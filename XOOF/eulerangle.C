// -*- C++ -*-
// $RCSfile: eulerangle.C,v $
// $Revision: 1.5 $
// $Author: langer $
// $Date: 2000-09-06 20:10:57 $

/* This software was produced by NIST, an agency of the U.S. government,
 * and by statute is not subject to copyright in the United States.
 * Recipients of this software assume all responsibilities associated
 * with its operation, modification and maintenance. However, to
 * facilitate maintenance we ask that before distributing modifed
 * versions of this software, you first contact the authors at
 * oof_manager@ctcms.nist.gov. 
 */


/* 3D Euler angle rotation
 *     alpha = polar declination
 *     beta = azimuthal rotation
 *     gamma = axial twist
 * For input, operator>> accepts two formats:
 *    [alpha, beta, gamma]
 * and
 *    beta
 * Any of the numbers can be replaced by the letter 'r', and an
 * angle will be generated with the appropriate random distribution.
 */
 
#include "eulerangle.h"
#include "random.h"
#include "ctype.h"
#include <math.h>
#ifdef HAVE_IEEEFP_H
#include <ieeefp.h>   // for finite(), which is sometimes not in math.h
#endif

static const double DEGREES = 180/M_PI;
static const double RADIANS = M_PI/180;

EulerAngle::EulerAngle(const EulerAngle &ea) {
  alpha_ = ea.alpha_;
  beta_ = ea.beta_;
  gamma_ = ea.gamma_;
}

EulerAngle::EulerAngle(const SphereCoord &sc) {
  alpha_ = sc.phi_;
  beta_ = sc.theta_;
  gamma_ = 0;
}

EulerAngle &EulerAngle::operator=(const EulerAngle &ea) {
  if(this != &ea) {
    alpha_ = ea.alpha_;
    beta_ = ea.beta_;
    gamma_ = ea.gamma_;
  }
  return *this;
}

ostream &operator<<(ostream &os, const EulerAngle &ea) {
    if(ea.alpha_ == 0.0 && ea.gamma_ == 0.0)
	os << DEGREES*ea.beta_;
    else
	os << "[" << DEGREES*ea.alpha_ << ", " << DEGREES*ea.beta_ << ", "
	    << DEGREES*ea.gamma_ << "]";
    return os;
}

static void skipspace(istream &is) {
  int ch;
  while(ch = is.get()) {
    if(!isspace(ch)) {
      is.putback(ch);
      return;
    }
  }
}
  
static int israndom(istream &is) {
  skipspace(is);
  int ch = is.get();
  if(ch == 'r') return 1;
  is.putback(ch);
  return 0;
}


istream &operator>>(istream &is, EulerAngle &ea) {
  int ch;
  if((ch = is.get()) != '[') {
    if(isdigit(ch) || ch == '.' || ch == '-') { /* single number */
      is.putback(ch);
      is >> ea.beta_;
      if(!is) return is;
      ea.beta_ *= RADIANS;
      ea.alpha_ = ea.gamma_ = 0.0;
      return is;
    }
    else if(ch == 'r') {	// construct a random angle
      ea.alpha_ = acos(2*rndm() - 1.0);
      ea.beta_ = 2*M_PI*rndm();
      ea.gamma_ = 2*M_PI*rndm();
      return is;
    }
    // not a single number, "r", or start of a triple in square brackets
    is.clear(ios::badbit | is.rdstate());
    return is;
  }
  
  if(israndom(is))
    ea.alpha_ = acos(2*rndm() - 1.0);
  else {
    is >> ea.alpha_;
    if(!is) return is;
    ea.alpha_ *= RADIANS;
  }

  skipspace(is);    
  if((ch = is.get()) != ',') {
    is.clear(ios::badbit | is.rdstate());
    return is;
  }

  if(israndom(is))
    ea.beta_ = 2*M_PI*rndm();
  else {
    is >> ea.beta_;
    if(!is) return is;
    ea.beta_ *= RADIANS;
  }

  skipspace(is);
  if((ch = is.get()) != ',') {
    is.clear(ios::badbit | is.rdstate());
    return is;
  }

  if(israndom(is)) 
    ea.gamma_ = 2*M_PI*rndm();
  else {
    is >> ea.gamma_;
    if(!is) return is;
    ea.gamma_ *= RADIANS;
  }

  skipspace(is);
  if((ch = is.get()) != ']') {
    is.clear(ios::badbit | is.rdstate());
    return is;
  }
  return is;
}

void sincos(const double angle, double &sine, double &cosine) {
    double tn = tan(0.5*angle);
    if(!finite(tn)) {
      sine = sin(angle);
      cosine = cos(angle);
      return;
    }
    double tntn = 1./(1 + tn*tn);
    cosine = (1 - tn*tn)*tntn;
    sine = 2*tn*tntn;
}

// Compute the rotation matrix corresponding to the Euler angle. The
// rotation matrix multiplied by a vector gives the coordinates of the
// vector in a coordinate system that has been rotated by the Euler
// angle.

MV_ColMat_double EulerAngle::rotation() const {

  double cosa, sina, cosb, sinb, cosg, sing;
  sincos(alpha_, sina, cosa);
  sincos(beta_, sinb, cosb);
  sincos(gamma_, sing, cosg);
  
  MV_ColMat_double r(3, 3);
   r(0, 0) =  cosa*cosb*cosg - sinb*sing;
   r(0, 1) =  cosa*sinb*cosg + cosb*sing;
   r(0, 2) = -sina*cosg;
   r(1, 0) = -cosa*cosb*sing - sinb*cosg;
   r(1, 1) = -cosa*sinb*sing + cosb*cosg;
   r(1, 2) =  sina*sing;
   r(2, 0) =  sina*cosb;
   r(2, 1) =  sina*sinb;
   r(2, 2) =  cosa;

  // steve's definition...
//  r(0, 0) =  cosa*cosb*cosg - sinb*sing;
//  r(0, 1) = -cosa*sinb*cosg - cosb*sing;
//  r(0, 2) =  sina*cosg;
//  r(1, 0) =  cosa*cosb*sing + sinb*cosg;
//  r(1, 1) = -cosa*sinb*sing + cosb*cosg;
//  r(1, 2) =  sina*sing;
//  r(2, 0) = -sina*cosb;
//  r(2, 1) =  sina*sinb;
//  r(2, 2) =  cosa;
  return r;
}

int operator==(const EulerAngle &om1, const EulerAngle &om2) {
  if(om1.alpha_ != om2.alpha_) return 0;
  if(om1.beta_ != om2.beta_) return 0;
  if(om1.gamma_ != om2.gamma_) return 0;
  return 1;
}

//-\\-//-\\-//-\\-//-\\-//-\\-//-\\-//-\\-//-\\-//-\\-//-\\-//-\\-//

SphereCoord::SphereCoord(const MV_Vector_double &v) {
  double len = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
  if(len == 0) {
    theta_ = 0;
    phi_ = 0;
  }
  phi_ = acos(v[2]/len);
  theta_ = atan2(v[1], v[0]);
}

SphereCoord::SphereCoord(const double * const v) {
  double len = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
  if(len == 0) {
    theta_ = 0;
    phi_ = 0;
  }
  phi_ = acos(v[2]/len);
  theta_ = atan2(v[1], v[0]);
}

// Compute the rotation matrix corresponding to the SphereCoord
// angle. The rotation matrix multiplied by a vector gives the
// coordinates of the vector in a coordinate system in which the z
// axis lies in the direction of the SphereCoord.

MV_ColMat_double SphereCoord::rotation() const {
  double sintheta, sinphi, costheta, cosphi;
  sincos(phi_, sinphi, cosphi);
  sincos(theta_, sintheta, costheta);
  MV_ColMat_double r(3,3);
  r(0,0) = costheta*cosphi;
  r(0,1) = sintheta*cosphi;
  r(0,2) = -sinphi;
  r(1,0) = -sintheta;
  r(1,1) = costheta;
  r(1,2) = 0;
  r(2,0) = costheta*sinphi;
  r(2,1) = sintheta*sinphi;
  r(2,2) = cosphi;
  return r;
}

ostream &operator<<(ostream &os, const SphereCoord &sc) {
  if(sc.phi_ == M_PI_2)
    os << sc.theta_*DEGREES;
  else
    os << "[" << sc.theta_*DEGREES << ", " << sc.phi_*DEGREES << "]";
  return os;
}


