/*
  Copyright 1999 ImageMagick Studio LLC, a non-profit organization
  dedicated to making software imaging solutions freely available.

  You may not use this file except in compliance with the License.  You may
  obtain a copy of the License at

    https://imagemagick.org/script/license.php

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  MagickCore private graphic gems methods.
*/
#ifndef MAGICKCORE_GEM_PRIVATE_H
#define MAGICKCORE_GEM_PRIVATE_H

#include "magick/pixel-accessor.h"
#include "magick/visual-effects.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

#define D65X  0.95047
#define D65Y  1.0
#define D65Z  1.08883
#define CIEEpsilon  (216.0/24389.0)
#define CIEK  (24389.0/27.0)

static inline void ConvertLabToXYZ(const double L,const double a,const double b,
  double *X,double *Y,double *Z)
{
  double
    x,
    y,
    z;

  assert(X != (double *) NULL);
  assert(Y != (double *) NULL);
  assert(Z != (double *) NULL);
  y=(L+16.0)/116.0;
  x=y+a/500.0;
  z=y-b/200.0;
  if ((x*x*x) > CIEEpsilon)
    x=(x*x*x);
  else
    x=(116.0*x-16.0)/CIEK;
  if (L > (CIEK*CIEEpsilon))
    y=(y*y*y);
  else
    y=L/CIEK;
  if ((z*z*z) > CIEEpsilon)
    z=(z*z*z);
  else
    z=(116.0*z-16.0)/CIEK;
  *X=D65X*x;
  *Y=D65Y*y;
  *Z=D65Z*z;
}

static inline void ConvertXYZToLuv(const double X,const double Y,const double Z,
  double *L,double *u,double *v)
{
  double
    alpha;

  assert(L != (double *) NULL);
  assert(u != (double *) NULL);
  assert(v != (double *) NULL);
  if ((Y/D65Y) > CIEEpsilon)
    *L=(double) (116.0*pow(Y/D65Y,1.0/3.0)-16.0);
  else
    *L=CIEK*(Y/D65Y);
  alpha=MagickSafeReciprocal(X+15.0*Y+3.0*Z);
  *u=13.0*(*L)*((4.0*alpha*X)-(4.0*D65X/(D65X+15.0*D65Y+3.0*D65Z)));
  *v=13.0*(*L)*((9.0*alpha*Y)-(9.0*D65Y/(D65X+15.0*D65Y+3.0*D65Z)));
  *L/=100.0;
  *u=(*u+134.0)/354.0;
  *v=(*v+140.0)/262.0;
}

static inline void ConvertRGBToXYZ(const Quantum red,const Quantum green,
  const Quantum blue,double *X,double *Y,double *Z)
{
  double
    b,
    g,
    r;

  assert(X != (double *) NULL);
  assert(Y != (double *) NULL);
  assert(Z != (double *) NULL);
  r=QuantumScale*DecodePixelGamma((MagickRealType) red);
  g=QuantumScale*DecodePixelGamma((MagickRealType) green);
  b=QuantumScale*DecodePixelGamma((MagickRealType) blue);
  *X=(0.4123955889674142161*r)+(0.3575834307637148171*g)+
    (0.1804926473817015735*b);
  *Y=(0.2125862307855955516*r)+(0.7151703037034108499*g)+
    (0.07220049864333622685*b);
  *Z=(0.01929721549174694484*r)+(0.1191838645808485318*g)+
    (0.9504971251315797660*b);
}

static inline void ConvertXYZToLab(const double X,const double Y,const double Z,
  double *L,double *a,double *b)
{
  double
    x,
    y,
    z;

  assert(L != (double *) NULL);
  assert(a != (double *) NULL);
  assert(b != (double *) NULL);
  if ((X/D65X) > CIEEpsilon)
    x=pow(X/D65X,1.0/3.0);
  else
    x=(CIEK*X/D65X+16.0)/116.0;
  if ((Y/D65Y) > CIEEpsilon)
    y=pow(Y/D65Y,1.0/3.0);
  else
    y=(CIEK*Y/D65Y+16.0)/116.0;
  if ((Z/D65Z) > CIEEpsilon)
    z=pow(Z/D65Z,1.0/3.0);
  else
    z=(CIEK*Z/D65Z+16.0)/116.0;
  *L=((116.0*y)-16.0)/100.0;
  *a=(500.0*(x-y))/255.0+0.5;
  *b=(200.0*(y-z))/255.0+0.5;
}

static inline void ConvertLuvToXYZ(const double L,const double u,const double v,
  double *X,double *Y,double *Z)
{
  double
    gamma;

  assert(X != (double *) NULL);
  assert(Y != (double *) NULL);
  assert(Z != (double *) NULL);
  if (L > (CIEK*CIEEpsilon))
    *Y=(double) pow((L+16.0)/116.0,3.0);
  else
    *Y=L/CIEK;
  gamma=MagickSafeReciprocal((((52.0*L*MagickSafeReciprocal(u+13.0*L* 
    (4.0*D65X/(D65X+15.0*D65Y+3.0*D65Z))))-1.0)/3.0)-(-1.0/3.0));
  *X=gamma*((*Y*((39.0*L*MagickSafeReciprocal(v+13.0*L*(9.0*D65Y/
    (D65X+15.0*D65Y+3.0*D65Z))))-5.0))+5.0*(*Y));
  *Z=(*X*(((52.0*L*MagickSafeReciprocal(u+13.0*L*(4.0*D65X/
    (D65X+15.0*D65Y+3.0*D65Z))))-1.0)/3.0))-5.0*(*Y);
}

static inline void ConvertXYZToRGB(const double X,const double Y,const double Z,
  Quantum *red,Quantum *green,Quantum *blue)
{
  double
    b,
    g,
    min,
    r;

  assert(red != (Quantum *) NULL);
  assert(green != (Quantum *) NULL);
  assert(blue != (Quantum *) NULL);
  r=(3.240969941904521*X)+(-1.537383177570093*Y)+(-0.498610760293*Z);
  g=(-0.96924363628087*X)+(1.87596750150772*Y)+(0.041555057407175*Z);
  b=(0.055630079696993*X)+(-0.20397695888897*Y)+(1.056971514242878*Z);
  min=MagickMin(r,MagickMin(g,b));
  if (min < 0.0)
    {
      r-=min;
      g-=min;
      b-=min;
    }
  *red=ClampToQuantum((MagickRealType) EncodePixelGamma((MagickRealType)
    QuantumRange*r));
  *green=ClampToQuantum((MagickRealType) EncodePixelGamma((MagickRealType)
    QuantumRange*g));
  *blue=ClampToQuantum((MagickRealType) EncodePixelGamma((MagickRealType)
    QuantumRange*b));
}

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
