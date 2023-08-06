/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%                                 FFFFF  X   X                                %
%                                 F       X X                                 %
%                                 FFF      X                                  %
%                                 F       X X                                 %
%                                 F      X   X                                %
%                                                                             %
%                                                                             %
%                   MagickCore Image Special Effects Methods                  %
%                                                                             %
%                               Software Design                               %
%                                    Cristy                                   %
%                                 October 1996                                %
%                                                                             %
%                                                                             %
%  Copyright 1999 ImageMagick Studio LLC, a non-profit organization           %
%  dedicated to making software imaging solutions freely available.           %
%                                                                             %
%  You may not use this file except in compliance with the License.  You may  %
%  obtain a copy of the License at                                            %
%                                                                             %
%    https://imagemagick.org/script/license.php                               %
%                                                                             %
%  Unless required by applicable law or agreed to in writing, software        %
%  distributed under the License is distributed on an "AS IS" BASIS,          %
%  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   %
%  See the License for the specific language governing permissions and        %
%  limitations under the License.                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%
%
*/

/*
  Include declarations.
*/
#include "magick/studio.h"
#include "magick/accelerate-private.h"
#include "magick/annotate.h"
#include "magick/artifact.h"
#include "magick/attribute.h"
#include "magick/cache.h"
#include "magick/cache-view.h"
#include "magick/channel.h"
#include "magick/color.h"
#include "magick/color-private.h"
#include "magick/colorspace.h"
#include "magick/colorspace-private.h"
#include "magick/composite.h"
#include "magick/decorate.h"
#include "magick/distort.h"
#include "magick/draw.h"
#include "magick/effect.h"
#include "magick/enhance.h"
#include "magick/exception.h"
#include "magick/exception-private.h"
#include "magick/fx.h"
#include "magick/fx-private.h"
#include "magick/gem.h"
#include "magick/geometry.h"
#include "magick/layer.h"
#include "magick/list.h"
#include "magick/log.h"
#include "magick/image.h"
#include "magick/image-private.h"
#include "magick/magick.h"
#include "magick/memory_.h"
#include "magick/memory-private.h"
#include "magick/monitor.h"
#include "magick/monitor-private.h"
#include "magick/opencl-private.h"
#include "magick/option.h"
#include "magick/pixel-accessor.h"
#include "magick/pixel-private.h"
#include "magick/property.h"
#include "magick/quantum.h"
#include "magick/quantum-private.h"
#include "magick/random_.h"
#include "magick/random-private.h"
#include "magick/resample.h"
#include "magick/resample-private.h"
#include "magick/resize.h"
#include "magick/resource_.h"
#include "magick/splay-tree.h"
#include "magick/statistic.h"
#include "magick/statistic-private.h"
#include "magick/string_.h"
#include "magick/string-private.h"
#include "magick/thread-private.h"
#include "magick/threshold.h"
#include "magick/token.h"
#include "magick/transform.h"
#include "magick/utility.h"

/*
  Define declarations.
*/
typedef enum
{
  BitwiseAndAssignmentOperator = 0xd9U,
  BitwiseOrAssignmentOperator,
  LeftShiftAssignmentOperator,
  RightShiftAssignmentOperator,
  PowerAssignmentOperator,
  ModuloAssignmentOperator,
  PlusAssignmentOperator,
  SubtractAssignmentOperator,
  MultiplyAssignmentOperator,
  DivideAssignmentOperator,
  IncrementAssignmentOperator,
  DecrementAssignmentOperator,
  LeftShiftOperator,
  RightShiftOperator,
  LessThanEqualOperator,
  GreaterThanEqualOperator,
  EqualOperator,
  NotEqualOperator,
  LogicalAndOperator,
  LogicalOrOperator,
  ExponentialNotation
} FxOperator;

struct _FxInfo
{
  const Image
    *images;

  char
    *expression;

  FILE
    *file;

  SplayTreeInfo
    *colors,
    *symbols;

  CacheView
    **view;

  RandomInfo
    *random_info;

  ExceptionInfo
    *exception;
};

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   A c q u i r e F x I n f o                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  AcquireFxInfo() allocates the FxInfo structure.
%
%  The format of the AcquireFxInfo method is:
%
%      FxInfo *AcquireFxInfo(Image *images,const char *expression)
%
%  A description of each parameter follows:
%
%    o images: the image sequence.
%
%    o expression: the expression.
%
*/
MagickExport FxInfo *AcquireFxInfo(const Image *images,const char *expression)
{
  const Image
    *next;

  FxInfo
    *fx_info;

  ssize_t
    i;

  unsigned char
    fx_op[2];

  fx_info=(FxInfo *) AcquireCriticalMemory(sizeof(*fx_info));
  (void) memset(fx_info,0,sizeof(*fx_info));
  fx_info->exception=AcquireExceptionInfo();
  fx_info->images=images;
  fx_info->colors=NewSplayTree(CompareSplayTreeString,RelinquishMagickMemory,
    RelinquishMagickMemory);
  fx_info->symbols=NewSplayTree(CompareSplayTreeString,RelinquishMagickMemory,
    RelinquishMagickMemory);
  fx_info->view=(CacheView **) AcquireQuantumMemory(GetImageListLength(
    fx_info->images),sizeof(*fx_info->view));
  if (fx_info->view == (CacheView **) NULL)
    ThrowFatalException(ResourceLimitFatalError,"MemoryAllocationFailed");
  i=0;
  next=GetFirstImageInList(fx_info->images);
  for ( ; next != (Image *) NULL; next=next->next)
  {
    fx_info->view[i]=AcquireVirtualCacheView(next,fx_info->exception);
    i++;
  }
  fx_info->random_info=AcquireRandomInfo();
  fx_info->expression=ConstantString(expression);
  fx_info->file=stderr;
  /*
    Convert compound to simple operators.
  */
  fx_op[1]='\0';
  *fx_op=(unsigned char) BitwiseAndAssignmentOperator;
  (void) SubstituteString(&fx_info->expression,"&=",(char *) fx_op);
  *fx_op=(unsigned char) BitwiseOrAssignmentOperator;
  (void) SubstituteString(&fx_info->expression,"|=",(char *) fx_op);
  *fx_op=(unsigned char) LeftShiftAssignmentOperator;
  (void) SubstituteString(&fx_info->expression,"<<=",(char *) fx_op);
  *fx_op=(unsigned char) RightShiftAssignmentOperator;
  (void) SubstituteString(&fx_info->expression,">>=",(char *) fx_op);
  *fx_op=(unsigned char) PowerAssignmentOperator;
  (void) SubstituteString(&fx_info->expression,"^=",(char *) fx_op);
  *fx_op=(unsigned char) ModuloAssignmentOperator;
  (void) SubstituteString(&fx_info->expression,"%=",(char *) fx_op);
  *fx_op=(unsigned char) PlusAssignmentOperator;
  (void) SubstituteString(&fx_info->expression,"+=",(char *) fx_op);
  *fx_op=(unsigned char) SubtractAssignmentOperator;
  (void) SubstituteString(&fx_info->expression,"-=",(char *) fx_op);
  *fx_op=(unsigned char) MultiplyAssignmentOperator;
  (void) SubstituteString(&fx_info->expression,"*=",(char *) fx_op);
  *fx_op=(unsigned char) DivideAssignmentOperator;
  (void) SubstituteString(&fx_info->expression,"/=",(char *) fx_op);
  *fx_op=(unsigned char) IncrementAssignmentOperator;
  (void) SubstituteString(&fx_info->expression,"++",(char *) fx_op);
  *fx_op=(unsigned char) DecrementAssignmentOperator;
  (void) SubstituteString(&fx_info->expression,"--",(char *) fx_op);
  *fx_op=(unsigned char) LeftShiftOperator;
  (void) SubstituteString(&fx_info->expression,"<<",(char *) fx_op);
  *fx_op=(unsigned char) RightShiftOperator;
  (void) SubstituteString(&fx_info->expression,">>",(char *) fx_op);
  *fx_op=(unsigned char) LessThanEqualOperator;
  (void) SubstituteString(&fx_info->expression,"<=",(char *) fx_op);
  *fx_op=(unsigned char) GreaterThanEqualOperator;
  (void) SubstituteString(&fx_info->expression,">=",(char *) fx_op);
  *fx_op=(unsigned char) EqualOperator;
  (void) SubstituteString(&fx_info->expression,"==",(char *) fx_op);
  *fx_op=(unsigned char) NotEqualOperator;
  (void) SubstituteString(&fx_info->expression,"!=",(char *) fx_op);
  *fx_op=(unsigned char) LogicalAndOperator;
  (void) SubstituteString(&fx_info->expression,"&&",(char *) fx_op);
  *fx_op=(unsigned char) LogicalOrOperator;
  (void) SubstituteString(&fx_info->expression,"||",(char *) fx_op);
  *fx_op=(unsigned char) ExponentialNotation;
  (void) SubstituteString(&fx_info->expression,"**",(char *) fx_op);
  /*
    Force right-to-left associativity for unary negation.
  */
  (void) SubstituteString(&fx_info->expression,"-","-1.0*");
  (void) SubstituteString(&fx_info->expression,"^-1.0*","^-");
  (void) SubstituteString(&fx_info->expression,"E-1.0*","E-");
  (void) SubstituteString(&fx_info->expression,"e-1.0*","e-");
  (void) SubstituteString(&fx_info->expression," ","");  /* compact string */
  return(fx_info);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   D e s t r o y F x I n f o                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DestroyFxInfo() deallocates memory associated with an FxInfo structure.
%
%  The format of the DestroyFxInfo method is:
%
%      ImageInfo *DestroyFxInfo(ImageInfo *fx_info)
%
%  A description of each parameter follows:
%
%    o fx_info: the fx info.
%
*/
MagickExport FxInfo *DestroyFxInfo(FxInfo *fx_info)
{
  ssize_t
    i;

  fx_info->exception=DestroyExceptionInfo(fx_info->exception);
  fx_info->expression=DestroyString(fx_info->expression);
  fx_info->symbols=DestroySplayTree(fx_info->symbols);
  fx_info->colors=DestroySplayTree(fx_info->colors);
  for (i=(ssize_t) GetImageListLength(fx_info->images)-1; i >= 0; i--)
    fx_info->view[i]=DestroyCacheView(fx_info->view[i]);
  fx_info->view=(CacheView **) RelinquishMagickMemory(fx_info->view);
  fx_info->random_info=DestroyRandomInfo(fx_info->random_info);
  fx_info=(FxInfo *) RelinquishMagickMemory(fx_info);
  return(fx_info);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+     F x E v a l u a t e C h a n n e l E x p r e s s i o n                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  FxEvaluateChannelExpression() evaluates an expression and returns the
%  results.
%
%  The format of the FxEvaluateExpression method is:
%
%      MagickBooleanType FxEvaluateChannelExpression(FxInfo *fx_info,
%        const ChannelType channel,const ssize_t x,const ssize_t y,
%        double *alpha,Exceptioninfo *exception)
%      MagickBooleanType FxEvaluateExpression(FxInfo *fx_info,double *alpha,
%        Exceptioninfo *exception)
%
%  A description of each parameter follows:
%
%    o fx_info: the fx info.
%
%    o channel: the channel.
%
%    o x,y: the pixel position.
%
%    o alpha: the result.
%
%    o exception: return any errors or warnings in this structure.
%
*/

static inline const double *GetFxSymbolValue(FxInfo *fx_info,const char *symbol)
{
  return((const double *) GetValueFromSplayTree(fx_info->symbols,symbol));
}

static inline MagickBooleanType SetFxSymbolValue(
  FxInfo *magick_restrict fx_info,const char *magick_restrict symbol,
  const double value)
{
  double
    *object;

  object=(double *) GetValueFromSplayTree(fx_info->symbols,symbol);
  if (object != (double *) NULL)
    {
      *object=value;
      return(MagickTrue);
    }
  object=(double *) AcquireMagickMemory(sizeof(*object));
  if (object == (double *) NULL)
    {
      (void) ThrowMagickException(fx_info->exception,GetMagickModule(),
        ResourceLimitError,"MemoryAllocationFailed","`%s'",
        fx_info->images->filename);
      return(MagickFalse);
    }
  *object=value;
  return(AddValueToSplayTree(fx_info->symbols,ConstantString(symbol),object));
}

static double FxChannelStatistics(FxInfo *fx_info,const Image *image,
  ChannelType channel,const char *symbol,ExceptionInfo *exception)
{
  char
    channel_symbol[MaxTextExtent],
    key[MaxTextExtent];

  const double
    *value;

  double
    statistic;

  const char
    *p;

  for (p=symbol; (*p != '.') && (*p != '\0'); p++) ;
  *channel_symbol='\0';
  if (*p == '.')
    {
      ssize_t
        option;

      (void) CopyMagickString(channel_symbol,p+1,MaxTextExtent);
      option=ParseCommandOption(MagickChannelOptions,MagickTrue,channel_symbol);
      if (option >= 0)
        channel=(ChannelType) option;
    }
  (void) FormatLocaleString(key,MaxTextExtent,"%p.%.20g.%s",(void *) image,
    (double) channel,symbol);
  value=GetFxSymbolValue(fx_info,key);
  if (value != (const double *) NULL)
    return(QuantumScale*(*value));
  statistic=0.0;
  if (LocaleNCompare(symbol,"depth",5) == 0)
    {
      size_t
        depth;

      depth=GetImageChannelDepth(image,channel,exception);
      statistic=(double) depth;
    }
  if (LocaleNCompare(symbol,"kurtosis",8) == 0)
    {
      double
        kurtosis,
        skewness;

      (void) GetImageChannelKurtosis(image,channel,&kurtosis,&skewness,
        exception);
      statistic=kurtosis;
    }
  if (LocaleNCompare(symbol,"maxima",6) == 0)
    {
      double
        maxima,
        minima;

      (void) GetImageChannelRange(image,channel,&minima,&maxima,exception);
      statistic=maxima;
    }
  if (LocaleNCompare(symbol,"mean",4) == 0)
    {
      double
        mean,
        standard_deviation;

      (void) GetImageChannelMean(image,channel,&mean,&standard_deviation,
        exception);
      statistic=mean;
    }
  if (LocaleNCompare(symbol,"minima",6) == 0)
    {
      double
        maxima,
        minima;

      (void) GetImageChannelRange(image,channel,&minima,&maxima,exception);
      statistic=minima;
    }
  if (LocaleNCompare(symbol,"skewness",8) == 0)
    {
      double
        kurtosis,
        skewness;

      (void) GetImageChannelKurtosis(image,channel,&kurtosis,&skewness,
        exception);
      statistic=skewness;
    }
  if (LocaleNCompare(symbol,"standard_deviation",18) == 0)
    {
      double
        mean,
        standard_deviation;

      (void) GetImageChannelMean(image,channel,&mean,&standard_deviation,
        exception);
      statistic=standard_deviation;
    }
  if (SetFxSymbolValue(fx_info,key,statistic) == MagickFalse)
    return(0.0);
  return(QuantumScale*statistic);
}

static double
  FxEvaluateSubexpression(FxInfo *,const ChannelType,const ssize_t,
    const ssize_t,const char *,const size_t,double *,ExceptionInfo *);

static inline MagickBooleanType IsFxFunction(const char *expression,
  const char *name,const size_t length)
{
  int
    c;

  size_t
    i;

  for (i=0; i <= length; i++)
    if (expression[i] == '\0')
      return(MagickFalse);
  c=expression[length];
  if ((LocaleNCompare(expression,name,length) == 0) &&
      ((isspace((int) ((unsigned char) c)) == 0) || (c == '(')))
    return(MagickTrue);
  return(MagickFalse);
}

static inline double FxGCD(const double alpha,const double beta,
  const size_t depth)
{
#define FxMaxFunctionDepth  200
  
  if (alpha < beta) 
    return(FxGCD(beta,alpha,depth+1));
  if ((fabs(beta) < 0.001) || (depth >= FxMaxFunctionDepth))
    return(alpha); 
  return(FxGCD(beta,alpha-beta*floor(alpha/beta),depth+1));
}

static inline const char *FxSubexpression(const char *expression,
  ExceptionInfo *exception)
{
  const char
    *subexpression;

  ssize_t
    level;

  level=0;
  subexpression=expression;
  while ((*subexpression != '\0') &&
         ((level != 1) || (strchr(")",(int) *subexpression) == (char *) NULL)))
  {
    if (strchr("(",(int) *subexpression) != (char *) NULL)
      level++;
    else
      if (strchr(")",(int) *subexpression) != (char *) NULL)
        level--;
    subexpression++;
  }
  if (*subexpression == '\0')
    (void) ThrowMagickException(exception,GetMagickModule(),OptionError,
      "UnbalancedParenthesis","`%s'",expression);
  return(subexpression);
}

static double FxGetSymbol(FxInfo *fx_info,const ChannelType channel,
  const ssize_t x,const ssize_t y,const char *expression,const size_t depth,
  ExceptionInfo *exception)
{
  char
    *q,
    symbol[MaxTextExtent];

  const char
    *artifact,
    *p;

  const double
    *value;

  double
    alpha,
    beta;

  Image
    *image;

  MagickBooleanType
    status;

  MagickPixelPacket
    pixel;

  PointInfo
    point;

  ssize_t
    i;

  size_t
    level;

  p=expression;
  i=GetImageIndexInList(fx_info->images);
  level=0;
  point.x=(double) x;
  point.y=(double) y;
  if (isalpha((int) ((unsigned char) *(p+1))) == 0)
    {
      char
        *subexpression;

      subexpression=AcquireString(expression);
      if (strchr("suv",(int) *p) != (char *) NULL)
        {
          switch (*p)
          {
            case 's':
            default:
            {
              i=GetImageIndexInList(fx_info->images);
              break;
            }
            case 'u': i=0; break;
            case 'v': i=1; break;
          }
          p++;
          if (*p == '[')
            {
              level++;
              q=subexpression;
              for (p++; *p != '\0'; )
              {
                if (*p == '[')
                  level++;
                else
                  if (*p == ']')
                    {
                      level--;
                      if (level == 0)
                        break;
                    }
                *q++=(*p++);
              }
              *q='\0';
              alpha=FxEvaluateSubexpression(fx_info,channel,x,y,subexpression,
                depth,&beta,exception);
              i=(ssize_t) alpha;
              if (*p != '\0')
                p++;
            }
          if (*p == '.')
            p++;
        }
      if ((*p == 'p') && (isalpha((int) ((unsigned char) *(p+1))) == 0))
        {
          p++;
          if (*p == '{')
            {
              level++;
              q=subexpression;
              for (p++; *p != '\0'; )
              {
                if (*p == '{')
                  level++;
                else
                  if (*p == '}')
                    {
                      level--;
                      if (level == 0)
                        break;
                    }
                *q++=(*p++);
              }
              *q='\0';
              alpha=FxEvaluateSubexpression(fx_info,channel,x,y,subexpression,
                depth,&beta,exception);
              point.x=alpha;
              point.y=beta;
              if (*p != '\0')
                p++;
            }
          else
            if (*p == '[')
              {
                level++;
                q=subexpression;
                for (p++; *p != '\0'; )
                {
                  if (*p == '[')
                    level++;
                  else
                    if (*p == ']')
                      {
                        level--;
                        if (level == 0)
                          break;
                      }
                  *q++=(*p++);
                }
                *q='\0';
                alpha=FxEvaluateSubexpression(fx_info,channel,x,y,subexpression,
                  depth,&beta,exception);
                point.x+=alpha;
                point.y+=beta;
                if (*p != '\0')
                  p++;
              }
          if (*p == '.')
            p++;
        }
      subexpression=DestroyString(subexpression);
    }
  image=GetImageFromList(fx_info->images,i);
  if (image == (Image *) NULL)
    {
      (void) ThrowMagickException(exception,GetMagickModule(),OptionError,
        "NoSuchImage","`%s'",expression);
      return(0.0);
    }
  i=GetImageIndexInList(image);
  GetMagickPixelPacket(image,&pixel);
  status=InterpolateMagickPixelPacket(image,fx_info->view[i],image->interpolate,
    point.x,point.y,&pixel,exception);
  (void) status;
  if ((*p != '\0') && (*(p+1) != '\0') && (*(p+2) != '\0') &&
      (LocaleCompare(p,"intensity") != 0) && (LocaleCompare(p,"luma") != 0) &&
      (LocaleCompare(p,"luminance") != 0) && (LocaleCompare(p,"hue") != 0) &&
      (LocaleCompare(p,"saturation") != 0) &&
      (LocaleCompare(p,"lightness") != 0))
    {
      char
        name[MaxTextExtent];

      size_t
        length;

      (void) CopyMagickString(name,p,MaxTextExtent);
      length=strlen(name);
      for (q=name+length-1; q > name; q--)
      {
        if (*q == ')')
          break;
        if (*q == '.')
          {
            *q='\0';
            break;
          }
      }
      q=name;
      if ((*q != '\0') && (*(q+1) != '\0') && (*(q+2) != '\0') &&
          (GetFxSymbolValue(fx_info,name) == (const double *) NULL))
        {
          MagickPixelPacket
            *color;

          color=(MagickPixelPacket *) GetValueFromSplayTree(fx_info->colors,
            name);
          if (color != (MagickPixelPacket *) NULL)
            {
              pixel=(*color);
              p+=length;
            }
          else
            if (QueryMagickColor(name,&pixel,fx_info->exception) != MagickFalse)
              {
                (void) AddValueToSplayTree(fx_info->colors,ConstantString(name),
                  CloneMagickPixelPacket(&pixel));
                p+=length;
              }
        }
    }
  (void) CopyMagickString(symbol,p,MaxTextExtent);
  StripString(symbol);
  if (*symbol == '\0')
    {
      switch (channel)
      {
        case RedChannel: return(QuantumScale*pixel.red);
        case GreenChannel: return(QuantumScale*pixel.green);
        case BlueChannel: return(QuantumScale*pixel.blue);
        case OpacityChannel:
        {
          double
            alpha;

          if (pixel.matte == MagickFalse)
            return(1.0);
          alpha=(double) (QuantumScale*GetPixelAlpha(&pixel));
          return(alpha);
        }
        case IndexChannel:
        {
          if (image->colorspace != CMYKColorspace)
            {
              (void) ThrowMagickException(exception,GetMagickModule(),
                ImageError,"ColorSeparatedImageRequired","`%s'",
                image->filename);
              return(0.0);
            }
          return(QuantumScale*pixel.index);
        }
        case DefaultChannels:
          return(QuantumScale*GetMagickPixelIntensity(image,&pixel));
        default:
          break;
      }
      (void) ThrowMagickException(exception,GetMagickModule(),OptionError,
        "UnableToParseExpression","`%s'",p);
      return(0.0);
    }
  switch (*symbol)
  {
    case 'A':
    case 'a':
    {
      if (LocaleCompare(symbol,"a") == 0)
        return((double) (QuantumScale*GetPixelAlpha(&pixel)));
      break;
    }
    case 'B':
    case 'b':
    {
      if (LocaleCompare(symbol,"b") == 0)
        return(QuantumScale*pixel.blue);
      break;
    }
    case 'C':
    case 'c':
    {
      if (IsFxFunction(symbol,"channel",7) != MagickFalse)
        {
          GeometryInfo
            channel_info;

          MagickStatusType
            flags;

          flags=ParseGeometry(symbol+7,&channel_info);
          if (image->colorspace == CMYKColorspace)
            switch (channel)
            {
              case CyanChannel:
              {
                if ((flags & RhoValue) == 0)
                  return(0.0);
                return(channel_info.rho);
              }
              case MagentaChannel:
              {
                if ((flags & SigmaValue) == 0)
                  return(0.0);
                return(channel_info.sigma);
              }
              case YellowChannel:
              {
                if ((flags & XiValue) == 0)
                  return(0.0);
                return(channel_info.xi);
              }
              case BlackChannel:
              {
                if ((flags & PsiValue) == 0)
                  return(0.0);
                return(channel_info.psi);
              }
              case OpacityChannel:
              {
                if ((flags & ChiValue) == 0)
                  return(0.0);
                return(channel_info.chi);
              }
              default:
                return(0.0);
            }
          switch (channel)
          {
            case RedChannel:
            {
              if ((flags & RhoValue) == 0)
                return(0.0);
              return(channel_info.rho);
            }
            case GreenChannel:
            {
              if ((flags & SigmaValue) == 0)
                return(0.0);
              return(channel_info.sigma);
            }
            case BlueChannel:
            {
              if ((flags & XiValue) == 0)
                return(0.0);
              return(channel_info.xi);
            }
            case OpacityChannel:
            {
              if ((flags & PsiValue) == 0)
                return(0.0);
              return(channel_info.psi);
            }
            case IndexChannel:
            {
              if ((flags & ChiValue) == 0)
                return(0.0);
              return(channel_info.chi);
            }
            default:
              return(0.0);
          }
        }
      if (LocaleCompare(symbol,"c") == 0)
        return(QuantumScale*pixel.red);
      break;
    }
    case 'D':
    case 'd':
    {
      if (LocaleNCompare(symbol,"depth",5) == 0)
        return(FxChannelStatistics(fx_info,image,channel,symbol,exception));
      break;
    }
    case 'E':
    case 'e':
    {
      if (LocaleCompare(symbol,"extent") == 0)
        {
          if (image->extent != 0)
            return((double) image->extent);
          return((double) GetBlobSize(image));
        }
      break;
    }
    case 'G':
    case 'g':
    {
      if (LocaleCompare(symbol,"g") == 0)
        return(QuantumScale*pixel.green);
      break;
    }
    case 'K':
    case 'k':
    {
      if (LocaleNCompare(symbol,"kurtosis",8) == 0)
        return(FxChannelStatistics(fx_info,image,channel,symbol,exception));
      if (LocaleCompare(symbol,"k") == 0)
        {
          if (image->colorspace != CMYKColorspace)
            {
              (void) ThrowMagickException(exception,GetMagickModule(),
                OptionError,"ColorSeparatedImageRequired","`%s'",
                image->filename);
              return(0.0);
            }
          return(QuantumScale*pixel.index);
        }
      break;
    }
    case 'H':
    case 'h':
    {
      if (LocaleCompare(symbol,"h") == 0)
        return((double) image->rows);
      if (LocaleCompare(symbol,"hue") == 0)
        {
          double
            hue,
            lightness,
            saturation;

          ConvertRGBToHSL(ClampToQuantum(pixel.red),ClampToQuantum(pixel.green),
            ClampToQuantum(pixel.blue),&hue,&saturation,&lightness);
          return(hue);
        }
      break;
    }
    case 'I':
    case 'i':
    {
      if ((LocaleCompare(symbol,"image.depth") == 0) ||
          (LocaleCompare(symbol,"image.minima") == 0) ||
          (LocaleCompare(symbol,"image.maxima") == 0) ||
          (LocaleCompare(symbol,"image.mean") == 0) ||
          (LocaleCompare(symbol,"image.kurtosis") == 0) ||
          (LocaleCompare(symbol,"image.skewness") == 0) ||
          (LocaleCompare(symbol,"image.standard_deviation") == 0))
        return(FxChannelStatistics(fx_info,image,channel,symbol+6,exception));
      if (LocaleCompare(symbol,"image.resolution.x") == 0)
        return(image->x_resolution);
      if (LocaleCompare(symbol,"image.resolution.y") == 0)
        return(image->y_resolution);
      if (LocaleCompare(symbol,"intensity") == 0)
        return(QuantumScale*GetMagickPixelIntensity(image,&pixel));
      if (LocaleCompare(symbol,"i") == 0)
        return((double) x);
      break;
    }
    case 'J':
    case 'j':
    {
      if (LocaleCompare(symbol,"j") == 0)
        return((double) y);
      break;
    }
    case 'L':
    case 'l':
    {
      if (LocaleCompare(symbol,"lightness") == 0)
        {
          double
            hue,
            lightness,
            saturation;

          ConvertRGBToHSL(ClampToQuantum(pixel.red),ClampToQuantum(pixel.green),
            ClampToQuantum(pixel.blue),&hue,&saturation,&lightness);
          return(lightness);
        }
      if (LocaleCompare(symbol,"luma") == 0)
        {
          double
            luma;

          luma=0.212656*pixel.red+0.715158*pixel.green+0.072186*pixel.blue;
          return(QuantumScale*luma);
        }
      if (LocaleCompare(symbol,"luminance") == 0)
        {
          double
            luminance;

          luminance=0.212656*pixel.red+0.715158*pixel.green+0.072186*pixel.blue;
          return(QuantumScale*luminance);
        }
      break;
    }
    case 'M':
    case 'm':
    {
      if (LocaleNCompare(symbol,"maxima",6) == 0)
        return(FxChannelStatistics(fx_info,image,channel,symbol,exception));
      if (LocaleNCompare(symbol,"mean",4) == 0)
        return(FxChannelStatistics(fx_info,image,channel,symbol,exception));
      if (LocaleNCompare(symbol,"minima",6) == 0)
        return(FxChannelStatistics(fx_info,image,channel,symbol,exception));
      if (LocaleCompare(symbol,"m") == 0)
        return(QuantumScale*pixel.green);
      break;
    }
    case 'N':
    case 'n':
    {
      if (LocaleCompare(symbol,"n") == 0)
        return((double) GetImageListLength(fx_info->images));
      break;
    }
    case 'O':
    case 'o':
    {
      if (LocaleCompare(symbol,"o") == 0)
        return(QuantumScale*pixel.opacity);
      break;
    }
    case 'P':
    case 'p':
    {
      if (LocaleCompare(symbol,"page.height") == 0)
        return((double) image->page.height);
      if (LocaleCompare(symbol,"page.width") == 0)
        return((double) image->page.width);
      if (LocaleCompare(symbol,"page.x") == 0)
        return((double) image->page.x);
      if (LocaleCompare(symbol,"page.y") == 0)
        return((double) image->page.y);
      if (LocaleCompare(symbol,"printsize.x") == 0)
        return(PerceptibleReciprocal(image->x_resolution)*image->columns);
      if (LocaleCompare(symbol,"printsize.y") == 0)
        return(PerceptibleReciprocal(image->y_resolution)*image->rows);
      break;
    }
    case 'Q':
    case 'q':
    {
      if (LocaleCompare(symbol,"quality") == 0)
        return((double) image->quality);
      break;
    }
    case 'R':
    case 'r':
    {
      if (LocaleCompare(symbol,"resolution.x") == 0)
        return(image->x_resolution);
      if (LocaleCompare(symbol,"resolution.y") == 0)
        return(image->y_resolution);
      if (LocaleCompare(symbol,"r") == 0)
        return(QuantumScale*pixel.red);
      break;
    }
    case 'S':
    case 's':
    {
      if (LocaleCompare(symbol,"saturation") == 0)
        {
          double
            hue,
            lightness,
            saturation;

          ConvertRGBToHSL(ClampToQuantum(pixel.red),ClampToQuantum(pixel.green),
            ClampToQuantum(pixel.blue),&hue,&saturation,&lightness);
          return(saturation);
        }
      if (LocaleNCompare(symbol,"skewness",8) == 0)
        return(FxChannelStatistics(fx_info,image,channel,symbol,exception));
      if (LocaleNCompare(symbol,"standard_deviation",18) == 0)
        return(FxChannelStatistics(fx_info,image,channel,symbol,exception));
      break;
    }
    case 'T':
    case 't':
    {
      if (LocaleCompare(symbol,"t") == 0)
        return((double) GetImageIndexInList(fx_info->images));
      break;
    }
    case 'W':
    case 'w':
    {
      if (LocaleCompare(symbol,"w") == 0)
        return((double) image->columns);
      break;
    }
    case 'Y':
    case 'y':
    {
      if (LocaleCompare(symbol,"y") == 0)
        return(QuantumScale*pixel.blue);
      break;
    }
    case 'Z':
    case 'z':
    {
      if (LocaleCompare(symbol,"z") == 0)
        {
          double
            depth;

          depth=(double) GetImageChannelDepth(image,channel,fx_info->exception);
          return(depth);
        }
      break;
    }
    default:
      break;
  }
  value=GetFxSymbolValue(fx_info,symbol);
  if (value != (const double *) NULL)
    return(*value);
  artifact=GetImageArtifact(image,symbol);
  if (artifact != (const char *) NULL)
    return(StringToDouble(artifact,(char **) NULL));
  (void) ThrowMagickException(exception,GetMagickModule(),OptionError,
    "UndefinedVariable","`%s'",symbol);
  (void) SetFxSymbolValue(fx_info,symbol,0.0);
  return(0.0);
}

static const char *FxOperatorPrecedence(const char *expression,
  ExceptionInfo *exception)
{
  typedef enum
  {
    UndefinedPrecedence,
    NullPrecedence,
    BitwiseComplementPrecedence,
    ExponentPrecedence,
    ExponentialNotationPrecedence,
    MultiplyPrecedence,
    AdditionPrecedence,
    ShiftPrecedence,
    RelationalPrecedence,
    EquivalencyPrecedence,
    BitwiseAndPrecedence,
    BitwiseOrPrecedence,
    LogicalAndPrecedence,
    LogicalOrPrecedence,
    TernaryPrecedence,
    AssignmentPrecedence,
    CommaPrecedence,
    SeparatorPrecedence
  } FxPrecedence;

  FxPrecedence
    precedence,
    target;

  const char
    *subexpression;

  int
    c;

  size_t
    level;

  c=(-1);
  level=0;
  subexpression=(const char *) NULL;
  target=NullPrecedence;
  while ((c != '\0') && (*expression != '\0'))
  {
    precedence=UndefinedPrecedence;
    if ((isspace((int) ((unsigned char) *expression)) != 0) || (c == (int) '@'))
      {
        expression++;
        continue;
      }
    switch (*expression)
    {
      case 'A':
      case 'a':
      {
#if defined(MAGICKCORE_HAVE_ACOSH)
        if (IsFxFunction(expression,"acosh",5) != MagickFalse)
          {
            expression+=5;
            break;
          }
#endif
#if defined(MAGICKCORE_HAVE_ASINH)
        if (IsFxFunction(expression,"asinh",5) != MagickFalse)
          {
            expression+=5;
            break;
          }
#endif
#if defined(MAGICKCORE_HAVE_ATANH)
        if (IsFxFunction(expression,"atanh",5) != MagickFalse)
          {
            expression+=5;
            break;
          }
#endif
        if (IsFxFunction(expression,"atan2",5) != MagickFalse)
          {
            expression+=5;
            break;
          }
        break;
      }
      case 'E':
      case 'e':
      {
        if ((isdigit((int) ((unsigned char) c)) != 0) &&
            ((LocaleNCompare(expression,"E+",2) == 0) ||
             (LocaleNCompare(expression,"E-",2) == 0)))
          {
            expression+=2;  /* scientific notation */
            break;
          }
        break;
      }
      case 'J':
      case 'j':
      {
        if ((IsFxFunction(expression,"j0",2) != MagickFalse) ||
            (IsFxFunction(expression,"j1",2) != MagickFalse))
          {
            expression+=2;
            break;
          }
        break;
      }
      case '#':
      {
        while (isxdigit((int) ((unsigned char) *(expression+1))) != 0)
          expression++;
        break;
      }
      default:
        break;
    }
    if ((c == (int) '{') || (c == (int) '['))
      level++;
    else
      if ((c == (int) '}') || (c == (int) ']'))
        level--;
    if (level == 0)
      switch ((unsigned char) *expression)
      {
        case '~':
        case '!':
        {
          precedence=BitwiseComplementPrecedence;
          break;
        }
        case '^':
        case '@':
        {
          precedence=ExponentPrecedence;
          break;
        }
        default:
        {
          if (((c != 0) && ((isdigit((int) ((unsigned char) c)) != 0) ||
               (strchr(")",c) != (char *) NULL))) &&
              (((islower((int) ((unsigned char) *expression)) != 0) ||
               (strchr("(",(int) ((unsigned char) *expression)) != (char *) NULL)) ||
               ((isdigit((int) ((unsigned char) c)) == 0) &&
                (isdigit((int) ((unsigned char) *expression)) != 0))) &&
              (strchr("xy",(int) ((unsigned char) *expression)) == (char *) NULL))
            precedence=MultiplyPrecedence;
          break;
        }
        case '*':
        case '/':
        case '%':
        {
          precedence=MultiplyPrecedence;
          break;
        }
        case '+':
        case '-':
        {
          if ((strchr("(+-/*%:&^|<>~,",c) == (char *) NULL) ||
              (isalpha((int) ((unsigned char) c)) != 0))
            precedence=AdditionPrecedence;
          break;
        }
        case BitwiseAndAssignmentOperator:
        case BitwiseOrAssignmentOperator:
        case LeftShiftAssignmentOperator:
        case RightShiftAssignmentOperator:
        case PowerAssignmentOperator:
        case ModuloAssignmentOperator:
        case PlusAssignmentOperator:
        case SubtractAssignmentOperator:
        case MultiplyAssignmentOperator:
        case DivideAssignmentOperator:
        case IncrementAssignmentOperator:
        case DecrementAssignmentOperator:
        {
          precedence=AssignmentPrecedence;
          break;
        }
        case LeftShiftOperator:
        case RightShiftOperator:
        {
          precedence=ShiftPrecedence;
          break;
        }
        case '<':
        case LessThanEqualOperator:
        case GreaterThanEqualOperator:
        case '>':
        {
          precedence=RelationalPrecedence;
          break;
        }
        case EqualOperator:
        case NotEqualOperator:
        {
          precedence=EquivalencyPrecedence;
          break;
        }
        case '&':
        {
          precedence=BitwiseAndPrecedence;
          break;
        }
        case '|':
        {
          precedence=BitwiseOrPrecedence;
          break;
        }
        case LogicalAndOperator:
        {
          precedence=LogicalAndPrecedence;
          break;
        }
        case LogicalOrOperator:
        {
          precedence=LogicalOrPrecedence;
          break;
        }
        case ExponentialNotation:
        {
          precedence=ExponentialNotationPrecedence;
          break;
        }
        case ':':
        case '?':
        {
          precedence=TernaryPrecedence;
          break;
        }
        case '=':
        {
          precedence=AssignmentPrecedence;
          break;
        }
        case ',':
        {
          precedence=CommaPrecedence;
          break;
        }
        case ';':
        {
          precedence=SeparatorPrecedence;
          break;
        }
      }
    if ((precedence == BitwiseComplementPrecedence) ||
        (precedence == TernaryPrecedence) ||
        (precedence == AssignmentPrecedence))
      {
        if (precedence > target)
          {
            /*
              Right-to-left associativity.
            */
            target=precedence;
            subexpression=expression;
          }
      }
    else
      if (precedence >= target)
        {
          /*
            Left-to-right associativity.
          */
          target=precedence;
          subexpression=expression;
        }
    if (strchr("(",(int) *expression) != (char *) NULL)
      expression=FxSubexpression(expression,exception);
    c=(int) (*expression++);
  }
  return(subexpression);
}

static double FxEvaluateSubexpression(FxInfo *fx_info,const ChannelType channel,
  const ssize_t x,const ssize_t y,const char *expression,const size_t depth,
  double *beta,ExceptionInfo *exception)
{
#define FxMaxParenthesisDepth  58
#define FxMaxSubexpressionDepth  200
#define FxReturn(value) \
{ \
  subexpression=DestroyString(subexpression); \
  return(value); \
}
#define FxParseConditional(subexpression,sentinal,p,q) \
{ \
  p=subexpression; \
  for (q=(char *) p; (*q != (sentinal)) && (*q != '\0'); q++) \
    if (*q == '(') \
      { \
        for (q++; (*q != ')') && (*q != '\0'); q++); \
        if (*q == '\0') \
          break; \
      } \
  if (*q == '\0') \
    { \
      (void) ThrowMagickException(exception,GetMagickModule(), \
        OptionError,"UnableToParseExpression","`%s'",subexpression); \
      FxReturn(0.0); \
    } \
  if (strlen(q) == 1) \
    *(q+1)='\0'; \
  *q='\0'; \
}

  char
    *q,
    *subexpression;

  double
    alpha,
    gamma,
    sans,
    value;

  const char
    *p;

  *beta=0.0;
  sans=0.0;
  subexpression=AcquireString(expression);
  *subexpression='\0';
  if (depth > FxMaxSubexpressionDepth)
    {
      (void) ThrowMagickException(exception,GetMagickModule(),OptionError,
        "UnableToParseExpression","`%s'",expression);
      FxReturn(0.0);
    }
  if (exception->severity >= ErrorException)
    FxReturn(0.0);
  while (isspace((int) ((unsigned char) *expression)) != 0)
    expression++;
  if (*expression == '\0')
    FxReturn(0.0);
  p=FxOperatorPrecedence(expression,exception);
  if (p != (const char *) NULL)
    {
      (void) CopyMagickString(subexpression,expression,(size_t)
        (p-expression+1));
      alpha=FxEvaluateSubexpression(fx_info,channel,x,y,subexpression,depth+1,
        beta,exception);
      switch ((unsigned char) *p)
      {
        case '~':
        {
          *beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          *beta=(double) (~(size_t) *beta);
          FxReturn(*beta);
        }
        case '!':
        {
          *beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          FxReturn(*beta == 0.0 ? 1.0 : 0.0);
        }
        case '^':
        {
          *beta=pow(alpha,FxEvaluateSubexpression(fx_info,channel,x,y,++p,
            depth+1,beta,exception));
          FxReturn(*beta);
        }
        case '*':
        case ExponentialNotation:
        {
          *beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          FxReturn(alpha*(*beta));
        }
        case '/':
        {
          *beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          FxReturn(PerceptibleReciprocal(*beta)*alpha);
        }
        case '%':
        {
          *beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          FxReturn(fmod(alpha,*beta));
        }
        case '+':
        {
          *beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          FxReturn(alpha+(*beta));
        }
        case '-':
        {
          *beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          FxReturn(alpha-(*beta));
        }
        case BitwiseAndAssignmentOperator:
        {
          q=subexpression;
          while (isalpha((int) ((unsigned char) *q)) != 0)
            q++;
          if (*q != '\0')
            {
              (void) ThrowMagickException(exception,GetMagickModule(),
                OptionError,"UnableToParseExpression","`%s'",subexpression);
              FxReturn(0.0);
            }
          ClearMagickException(exception);
          *beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          value=(double) ((size_t) (alpha+0.5) & (size_t) (*beta+0.5));
          if (SetFxSymbolValue(fx_info,subexpression,value) == MagickFalse)
            return(0.0);
          FxReturn(*beta);
        }
        case BitwiseOrAssignmentOperator:
        {
          q=subexpression;
          while (isalpha((int) ((unsigned char) *q)) != 0)
            q++;
          if (*q != '\0')
            {
              (void) ThrowMagickException(exception,GetMagickModule(),
                OptionError,"UnableToParseExpression","`%s'",subexpression);
              FxReturn(0.0);
            }
          ClearMagickException(exception);
          *beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          value=(double) ((size_t) (alpha+0.5) | (size_t) (*beta+0.5));
          if (SetFxSymbolValue(fx_info,subexpression,value) == MagickFalse)
            return(0.0);
          FxReturn(*beta);
        }
        case LeftShiftAssignmentOperator:
        {
          q=subexpression;
          while (isalpha((int) ((unsigned char) *q)) != 0)
            q++;
          if (*q != '\0')
            {
              (void) ThrowMagickException(exception,GetMagickModule(),
                OptionError,"UnableToParseExpression","`%s'",subexpression);
              FxReturn(0.0);
            }
          ClearMagickException(exception);
          *beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          if ((size_t) (*beta+0.5) >= (8*sizeof(size_t)))
            {
              (void) ThrowMagickException(exception,GetMagickModule(),
                OptionError,"ShiftCountOverflow","`%s'",subexpression);
              FxReturn(0.0);
            }
          value=(double) ((size_t) (alpha+0.5) << (size_t) (*beta+0.5));
          if (SetFxSymbolValue(fx_info,subexpression,value) == MagickFalse)
            return(0.0);
          FxReturn(*beta);
        }
        case RightShiftAssignmentOperator:
        {
          q=subexpression;
          while (isalpha((int) ((unsigned char) *q)) != 0)
            q++;
          if (*q != '\0')
            {
              (void) ThrowMagickException(exception,GetMagickModule(),
                OptionError,"UnableToParseExpression","`%s'",subexpression);
              FxReturn(0.0);
            }
          ClearMagickException(exception);
          *beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          if ((size_t) (*beta+0.5) >= (8*sizeof(size_t)))
            {
              (void) ThrowMagickException(exception,GetMagickModule(),
                OptionError,"ShiftCountOverflow","`%s'",subexpression);
              FxReturn(0.0);
            }
          value=(double) ((size_t) (alpha+0.5) >> (size_t) (*beta+0.5));
          if (SetFxSymbolValue(fx_info,subexpression,value) == MagickFalse)
            return(0.0);
          FxReturn(*beta);
        }
        case PowerAssignmentOperator:
        {
          q=subexpression;
          while (isalpha((int) ((unsigned char) *q)) != 0)
            q++;
          if (*q != '\0')
            {
              (void) ThrowMagickException(exception,GetMagickModule(),
                OptionError,"UnableToParseExpression","`%s'",subexpression);
              FxReturn(0.0);
            }
          ClearMagickException(exception);
          *beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          value=pow(alpha,*beta);
          if (SetFxSymbolValue(fx_info,subexpression,value) == MagickFalse)
            return(0.0);
          FxReturn(*beta);
        }
        case ModuloAssignmentOperator:
        {
          q=subexpression;
          while (isalpha((int) ((unsigned char) *q)) != 0)
            q++;
          if (*q != '\0')
            {
              (void) ThrowMagickException(exception,GetMagickModule(),
                OptionError,"UnableToParseExpression","`%s'",subexpression);
              FxReturn(0.0);
            }
          ClearMagickException(exception);
          *beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          value=fmod(alpha,*beta);
          if (SetFxSymbolValue(fx_info,subexpression,value) == MagickFalse)
            return(0.0);
          FxReturn(*beta);
        }
        case PlusAssignmentOperator:
        {
          q=subexpression;
          while (isalpha((int) ((unsigned char) *q)) != 0)
            q++;
          if (*q != '\0')
            {
              (void) ThrowMagickException(exception,GetMagickModule(),
                OptionError,"UnableToParseExpression","`%s'",subexpression);
              FxReturn(0.0);
            }
          ClearMagickException(exception);
          *beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          value=alpha+(*beta);
          if (SetFxSymbolValue(fx_info,subexpression,value) == MagickFalse)
            return(0.0);
          FxReturn(*beta);
        }
        case SubtractAssignmentOperator:
        {
          q=subexpression;
          while (isalpha((int) ((unsigned char) *q)) != 0)
            q++;
          if (*q != '\0')
            {
              (void) ThrowMagickException(exception,GetMagickModule(),
                OptionError,"UnableToParseExpression","`%s'",subexpression);
              FxReturn(0.0);
            }
          ClearMagickException(exception);
          *beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          value=alpha-(*beta);
          if (SetFxSymbolValue(fx_info,subexpression,value) == MagickFalse)
            return(0.0);
          FxReturn(*beta);
        }
        case MultiplyAssignmentOperator:
        {
          q=subexpression;
          while (isalpha((int) ((unsigned char) *q)) != 0)
            q++;
          if (*q != '\0')
            {
              (void) ThrowMagickException(exception,GetMagickModule(),
                OptionError,"UnableToParseExpression","`%s'",subexpression);
              FxReturn(0.0);
            }
          ClearMagickException(exception);
          *beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          value=alpha*(*beta);
          if (SetFxSymbolValue(fx_info,subexpression,value) == MagickFalse)
            return(0.0);
          FxReturn(*beta);
        }
       case DivideAssignmentOperator:
        {
          q=subexpression;
          while (isalpha((int) ((unsigned char) *q)) != 0)
            q++;
          if (*q != '\0')
            {
              (void) ThrowMagickException(exception,GetMagickModule(),
                OptionError,"UnableToParseExpression","`%s'",subexpression);
              FxReturn(0.0);
            }
          ClearMagickException(exception);
          *beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          value=alpha*PerceptibleReciprocal(*beta);
          if (SetFxSymbolValue(fx_info,subexpression,value) == MagickFalse)
            return(0.0);
          FxReturn(*beta);
        }
        case IncrementAssignmentOperator:
        {
          if (*subexpression == '\0')
            alpha=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
              exception);
          value=alpha+1.0;
          if (*subexpression == '\0')
            {
              if (SetFxSymbolValue(fx_info,p,value) == MagickFalse)
                return(0.0);
            }
          else
            if (SetFxSymbolValue(fx_info,subexpression,value) == MagickFalse)
              return(0.0);
          FxReturn(*beta);
        }
        case DecrementAssignmentOperator:
        {
          if (*subexpression == '\0')
            alpha=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
              exception);
          value=alpha-1.0;
          if (*subexpression == '\0')
            {
              if (SetFxSymbolValue(fx_info,p,value) == MagickFalse)
                return(0.0);
            }
          else
            if (SetFxSymbolValue(fx_info,subexpression,value) == MagickFalse)
              return(0.0);
          FxReturn(*beta);
        }
        case LeftShiftOperator:
        {
          gamma=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          if ((size_t) (gamma+0.5) >= (8*sizeof(size_t)))
            {
              (void) ThrowMagickException(exception,GetMagickModule(),
                OptionError,"ShiftCountOverflow","`%s'",subexpression);
              FxReturn(0.0);
            }
          *beta=(double) ((size_t) (alpha+0.5) << (size_t) (gamma+0.5));
          FxReturn(*beta);
        }
        case RightShiftOperator:
        {
          gamma=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          if ((size_t) (gamma+0.5) >= (8*sizeof(size_t)))
            {
              (void) ThrowMagickException(exception,GetMagickModule(),
                OptionError,"ShiftCountOverflow","`%s'",subexpression);
              FxReturn(0.0);
            }
          *beta=(double) ((size_t) (alpha+0.5) >> (size_t) (gamma+0.5));
          FxReturn(*beta);
        }
        case '<':
        {
          *beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          FxReturn(alpha < *beta ? 1.0 : 0.0);
        }
        case LessThanEqualOperator:
        {
          *beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          FxReturn(alpha <= *beta ? 1.0 : 0.0);
        }
        case '>':
        {
          *beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          FxReturn(alpha > *beta ? 1.0 : 0.0);
        }
        case GreaterThanEqualOperator:
        {
          *beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          FxReturn(alpha >= *beta ? 1.0 : 0.0);
        }
        case EqualOperator:
        {
          *beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          FxReturn(fabs(alpha-(*beta)) < MagickEpsilon ? 1.0 : 0.0);
        }
        case NotEqualOperator:
        {
          *beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          FxReturn(fabs(alpha-(*beta)) >= MagickEpsilon ? 1.0 : 0.0);
        }
        case '&':
        {
          gamma=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          *beta=(double) ((size_t) (alpha+0.5) & (size_t) (gamma+0.5));
          FxReturn(*beta);
        }
        case '|':
        {
          gamma=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          *beta=(double) ((size_t) (alpha+0.5) | (size_t) (gamma+0.5));
          FxReturn(*beta);
        }
        case LogicalAndOperator:
        {
          p++;
          if (alpha <= 0.0)
            {
              *beta=0.0;
              FxReturn(*beta);
            }
          gamma=FxEvaluateSubexpression(fx_info,channel,x,y,p,depth+1,beta,
            exception);
          *beta=(gamma > 0.0) ? 1.0 : 0.0;
          FxReturn(*beta);
        }
        case LogicalOrOperator:
        {
          p++;
          if (alpha > 0.0)
            {
             *beta=1.0;
             FxReturn(*beta);
            }
          gamma=FxEvaluateSubexpression(fx_info,channel,x,y,p,depth+1,beta,
            exception);
          *beta=(gamma > 0.0) ? 1.0 : 0.0;
          FxReturn(*beta);
        }
        case '?':
        {
          double
            gamma;

          (void) CopyMagickString(subexpression,++p,MaxTextExtent-1);
          FxParseConditional(subexpression,':',p,q);
          if (fabs(alpha) >= MagickEpsilon)
            gamma=FxEvaluateSubexpression(fx_info,channel,x,y,p,depth+1,beta,
              exception);
          else
            gamma=FxEvaluateSubexpression(fx_info,channel,x,y,q+1,depth+1,beta,
              exception);
          FxReturn(gamma);
        }
        case '=':
        {
          q=subexpression;
          while (isalpha((int) ((unsigned char) *q)) != 0)
            q++;
          if (*q != '\0')
            {
              (void) ThrowMagickException(exception,GetMagickModule(),
                OptionError,"UnableToParseExpression","`%s'",subexpression);
              FxReturn(0.0);
            }
          ClearMagickException(exception);
          *beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          value=(*beta);
          if (SetFxSymbolValue(fx_info,subexpression,value) == MagickFalse)
            return(0.0);
          FxReturn(*beta);
        }
        case ',':
        {
          *beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          FxReturn(alpha);
        }
        case ';':
        {
          *beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,beta,
            exception);
          if (*p == '\0')
            FxReturn(alpha);
          FxReturn(*beta);
        }
        default:
        {
          gamma=alpha*FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth+1,
            beta,exception);
          FxReturn(gamma);
        }
      }
    }
  if (strchr("(",(int) *expression) != (char *) NULL)
    {
      size_t
        length;

      if (depth >= FxMaxParenthesisDepth)
        (void) ThrowMagickException(exception,GetMagickModule(),OptionError,
          "ParenthesisNestedTooDeeply","`%s'",expression);
      length=CopyMagickString(subexpression,expression+1,MaxTextExtent);
      if (length != 0)
        subexpression[length-1]='\0';
      gamma=FxEvaluateSubexpression(fx_info,channel,x,y,subexpression,depth+1,
        beta,exception);
      FxReturn(gamma);
    }
  switch (*expression)
  {
    case '+':
    {
      gamma=FxEvaluateSubexpression(fx_info,channel,x,y,expression+1,depth+1,
        beta,exception);
      FxReturn(1.0*gamma);
    }
    case '-':
    {
      gamma=FxEvaluateSubexpression(fx_info,channel,x,y,expression+1,depth+1,
        beta,exception);
      FxReturn(-1.0*gamma);
    }
    case '~':
    {
      gamma=FxEvaluateSubexpression(fx_info,channel,x,y,expression+1,depth+1,
        beta,exception);
      FxReturn((double) (~(size_t) (gamma+0.5)));
    }
    case 'A':
    case 'a':
    {
      if (IsFxFunction(expression,"abs",3) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,
            depth+1,beta,exception);
          FxReturn(fabs(alpha));
        }
#if defined(MAGICKCORE_HAVE_ACOSH)
      if (IsFxFunction(expression,"acosh",5) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+5,
            depth+1,beta,exception);
          FxReturn(acosh(alpha));
        }
#endif
      if (IsFxFunction(expression,"acos",4) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+4,
            depth+1,beta,exception);
          FxReturn(acos(alpha));
        }
#if defined(MAGICKCORE_HAVE_J1)
      if (IsFxFunction(expression,"airy",4) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+4,
            depth+1,beta,exception);
          if (alpha == 0.0)
            FxReturn(1.0);
          gamma=2.0*j1((MagickPI*alpha))/(MagickPI*alpha);
          FxReturn(gamma*gamma);
        }
#endif
#if defined(MAGICKCORE_HAVE_ASINH)
      if (IsFxFunction(expression,"asinh",5) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+5,
            depth+1,beta,exception);
          FxReturn(asinh(alpha));
        }
#endif
      if (IsFxFunction(expression,"asin",4) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+4,
            depth+1,beta,exception);
          FxReturn(asin(alpha));
        }
      if (IsFxFunction(expression,"alt",3) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,
            depth+1,beta,exception);
          FxReturn(((ssize_t) alpha) & 0x01 ? -1.0 : 1.0);
        }
      if (IsFxFunction(expression,"atan2",5) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+5,
            depth+1,beta,exception);
          FxReturn(atan2(alpha,*beta));
        }
#if defined(MAGICKCORE_HAVE_ATANH)
      if (IsFxFunction(expression,"atanh",5) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+5,
            depth+1,beta,exception);
          FxReturn(atanh(alpha));
        }
#endif
      if (IsFxFunction(expression,"atan",4) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+4,
            depth+1,beta,exception);
          FxReturn(atan(alpha));
        }
      if (LocaleCompare(expression,"a") == 0)
        FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,depth+1,exception));
      break;
    }
    case 'B':
    case 'b':
    {
      if (LocaleCompare(expression,"b") == 0)
        FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,depth+1,exception));
      break;
    }
    case 'C':
    case 'c':
    {
      if (IsFxFunction(expression,"ceil",4) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+4,
            depth+1,beta,exception);
          FxReturn(ceil(alpha));
        }
      if (IsFxFunction(expression,"clamp",5) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+5,
            depth+1,beta,exception);
          if (alpha < 0.0)
            FxReturn(0.0);
          if (alpha > 1.0)
            FxReturn(1.0);
          FxReturn(alpha);
        }
      if (IsFxFunction(expression,"cosh",4) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+4,
            depth+1,beta,exception);
          FxReturn(cosh(alpha));
        }
      if (IsFxFunction(expression,"cos",3) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,
            depth+1,beta,exception);
          FxReturn(cos(alpha));
        }
      if (LocaleCompare(expression,"c") == 0)
        FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,depth+1,exception));
      break;
    }
    case 'D':
    case 'd':
    {
      if (IsFxFunction(expression,"debug",5) != MagickFalse)
        {
          const char
            *type;

          size_t
            length;

          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+5,
            depth+1,beta,exception);
          switch (fx_info->images->colorspace)
          {
            case CMYKColorspace:
            {
              switch (channel)
              {
                case CyanChannel: type="cyan"; break;
                case MagentaChannel: type="magenta"; break;
                case YellowChannel: type="yellow"; break;
                case AlphaChannel: type="alpha"; break;
                case BlackChannel: type="black"; break;
                default: type="unknown"; break;
              }
              break;
            }
            case GRAYColorspace:
            {
              switch (channel)
              {
                case RedChannel: type="gray"; break;
                case AlphaChannel: type="alpha"; break;
                default: type="unknown"; break;
              }
              break;
            }
            default:
            {
              switch (channel)
              {
                case RedChannel: type="red"; break;
                case GreenChannel: type="green"; break;
                case BlueChannel: type="blue"; break;
                case AlphaChannel: type="alpha"; break;
                default: type="unknown"; break;
              }
              break;
            }
          }
          *subexpression='\0';
          length=1;
          if (strlen(expression) > 6)
            length=CopyMagickString(subexpression,expression+6,MaxTextExtent);
          if (length != 0)
            subexpression[length-1]='\0';
          if (fx_info->file != (FILE *) NULL)
            (void) FormatLocaleFile(fx_info->file,
              "%s[%.20g,%.20g].%s: %s=%.*g\n",fx_info->images->filename,
              (double) x,(double) y,type,subexpression,GetMagickPrecision(),
              (double) alpha);
          FxReturn(alpha);
        }
      if (IsFxFunction(expression,"do",2) != MagickFalse)
        {
          size_t
            length;

          /*
            Parse do(expression,condition test).
          */
          length=CopyMagickString(subexpression,expression+6,
            MagickPathExtent-1);
          if (length != 0)
            subexpression[length-1]='\0';
          FxParseConditional(subexpression,',',p,q);
          for (alpha=0.0; ; )
          {
            alpha=FxEvaluateSubexpression(fx_info,channel,x,y,q+1,depth+1,beta,
              exception);
            gamma=FxEvaluateSubexpression(fx_info,channel,x,y,p,depth+1,&sans,
              exception);
            if (fabs(gamma) < MagickEpsilon)
              break;
          }
          FxReturn(alpha);
        }
      if (IsFxFunction(expression,"drc",3) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,
            depth+1,beta,exception);
          FxReturn(alpha*PerceptibleReciprocal(*beta*(alpha-1.0)+1.0));
        }
      break;
    }
    case 'E':
    case 'e':
    {
      if (LocaleCompare(expression,"epsilon") == 0)
        FxReturn(MagickEpsilon);
#if defined(MAGICKCORE_HAVE_ERF)
      if (IsFxFunction(expression,"erf",3) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,
            depth+1,beta,exception);
          FxReturn(erf(alpha));
        }
#endif
      if (IsFxFunction(expression,"exp",3) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,
            depth+1,beta,exception);
          FxReturn(exp(alpha));
        }
      if (LocaleCompare(expression,"e") == 0)
        FxReturn(2.7182818284590452354);
      break;
    }
    case 'F':
    case 'f':
    {
      if (IsFxFunction(expression,"floor",5) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+5,
            depth+1,beta,exception);
          FxReturn(floor(alpha));
        }
      if (IsFxFunction(expression,"for",3) != MagickFalse)
        {
          double
            sans = 0.0;

          size_t
            length;

          /*
            Parse for(initialization, condition test, expression).
          */
          length=CopyMagickString(subexpression,expression+4,
            MagickPathExtent-1);
          if (length != 0)
            subexpression[length-1]='\0';
          FxParseConditional(subexpression,',',p,q);
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,p,depth+1,&sans,
            exception);
          (void) CopyMagickString(subexpression,q+1,MagickPathExtent-1);
          FxParseConditional(subexpression,',',p,q);
          for (alpha=0.0; ; )
          {
            gamma=FxEvaluateSubexpression(fx_info,channel,x,y,p,depth+1,&sans,
              exception);
            if (fabs(gamma) < MagickEpsilon)
              break;
            alpha=FxEvaluateSubexpression(fx_info,channel,x,y,q+1,depth+1,beta,
              exception);
          }
          FxReturn(alpha);
        }
      break;
    }
    case 'G':
    case 'g':
    {
      if (IsFxFunction(expression,"gauss",5) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+5,
            depth+1,beta,exception);
          FxReturn(exp((-alpha*alpha/2.0))/sqrt(2.0*MagickPI));
        }
      if (IsFxFunction(expression,"gcd",3) != MagickFalse)
        {
          double
            gcd;

          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,
            depth+1,beta,exception);
          if (IsNaN(alpha))
            FxReturn(alpha);
          gcd=FxGCD(alpha,*beta,0);
          FxReturn(gcd);
        }
      if (LocaleCompare(expression,"g") == 0)
        FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,depth+1,exception));
      break;
    }
    case 'H':
    case 'h':
    {
      if (LocaleCompare(expression,"h") == 0)
        FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,depth+1,exception));
      if (LocaleCompare(expression,"hue") == 0)
        FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,depth+1,exception));
      if (IsFxFunction(expression,"hypot",5) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+5,
            depth+1,beta,exception);
          FxReturn(hypot(alpha,*beta));
        }
      break;
    }
    case 'K':
    case 'k':
    {
      if (LocaleCompare(expression,"k") == 0)
        FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,depth+1,exception));
      break;
    }
    case 'I':
    case 'i':
    {
     if (IsFxFunction(expression,"if",2) != MagickFalse)
        {
          double
            sans = 0.0;

          size_t
            length;

          /*
            Parse if(condition test, true-expression, false-expression).
          */
          length=CopyMagickString(subexpression,expression+3,
            MagickPathExtent-1);
          if (length != 0)
            subexpression[length-1]='\0';
          FxParseConditional(subexpression,',',p,q);
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,p,depth+1,&sans,
            exception);
          (void) CopyMagickString(subexpression,q+1,MagickPathExtent-1);
          FxParseConditional(subexpression,',',p,q);
          if (fabs(alpha) >= MagickEpsilon)
            alpha=FxEvaluateSubexpression(fx_info,channel,x,y,p,depth+1,beta,
              exception);
          else
            alpha=FxEvaluateSubexpression(fx_info,channel,x,y,q+1,depth+1,beta,
              exception);
          FxReturn(alpha);
        }
      if (LocaleCompare(expression,"intensity") == 0)
        FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,depth+1,exception));
      if (IsFxFunction(expression,"int",3) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,
            depth+1,beta,exception);
          FxReturn(floor(alpha));
        }
      if (IsFxFunction(expression,"isnan",5) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+5,
            depth+1,beta,exception);
          FxReturn((double) !!IsNaN(alpha));
        }
      if (LocaleCompare(expression,"i") == 0)
        FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,depth+1,exception));
      break;
    }
    case 'J':
    case 'j':
    {
      if (LocaleCompare(expression,"j") == 0)
        FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,depth+1,exception));
#if defined(MAGICKCORE_HAVE_J0)
      if (IsFxFunction(expression,"j0",2) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+2,
            depth+1,beta,exception);
          FxReturn(j0(alpha));
        }
#endif
#if defined(MAGICKCORE_HAVE_J1)
      if (IsFxFunction(expression,"j1",2) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+2,
            depth+1,beta,exception);
          FxReturn(j1(alpha));
        }
#endif
#if defined(MAGICKCORE_HAVE_J1)
      if (IsFxFunction(expression,"jinc",4) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+4,
            depth+1,beta,exception);
          if (alpha == 0.0)
            FxReturn(1.0);
          FxReturn((2.0*j1((MagickPI*alpha))/(MagickPI*alpha)));
        }
#endif
      break;
    }
    case 'L':
    case 'l':
    {
      if (IsFxFunction(expression,"ln",2) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+2,
            depth+1,beta,exception);
          FxReturn(log(alpha));
        }
      if (IsFxFunction(expression,"logtwo",6) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+6,
            depth+1,beta,exception);
          FxReturn(MagickLog10(alpha)/log10(2.0));
        }
      if (IsFxFunction(expression,"log",3) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,
            depth+1,beta,exception);
          FxReturn(MagickLog10(alpha));
        }
      if (LocaleCompare(expression,"lightness") == 0)
        FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,depth+1,exception));
      break;
    }
    case 'M':
    case 'm':
    {
      if (LocaleCompare(expression,"MaxRGB") == 0)
        FxReturn((double) QuantumRange);
      if (LocaleNCompare(expression,"maxima",6) == 0)
        break;
      if (IsFxFunction(expression,"max",3) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,
            depth+1,beta,exception);
          FxReturn(alpha > *beta ? alpha : *beta);
        }
      if (LocaleNCompare(expression,"minima",6) == 0)
        break;
      if (IsFxFunction(expression,"min",3) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,
            depth+1,beta,exception);
          FxReturn(alpha < *beta ? alpha : *beta);
        }
      if (IsFxFunction(expression,"mod",3) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,
            depth+1,beta,exception);
          FxReturn(alpha-floor((alpha*PerceptibleReciprocal(*beta)))*(*beta));
        }
      if (LocaleCompare(expression,"m") == 0)
        FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,depth+1,exception));
      break;
    }
    case 'N':
    case 'n':
    {
      if (IsFxFunction(expression,"not",3) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,
            depth+1,beta,exception);
          FxReturn((double) (alpha < MagickEpsilon));
        }
      if (LocaleCompare(expression,"n") == 0)
        FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,depth+1,exception));
      break;
    }
    case 'O':
    case 'o':
    {
      if (LocaleCompare(expression,"Opaque") == 0)
        FxReturn(1.0);
      if (LocaleCompare(expression,"o") == 0)
        FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,depth+1,exception));
      break;
    }
    case 'P':
    case 'p':
    {
      if (LocaleCompare(expression,"phi") == 0)
        FxReturn(MagickPHI);
      if (LocaleCompare(expression,"pi") == 0)
        FxReturn(MagickPI);
      if (IsFxFunction(expression,"pow",3) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,
            depth+1,beta,exception);
          FxReturn(pow(alpha,*beta));
        }
      if (LocaleCompare(expression,"p") == 0)
        FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,depth+1,exception));
      break;
    }
    case 'Q':
    case 'q':
    {
      if (LocaleCompare(expression,"QuantumRange") == 0)
        FxReturn((double) QuantumRange);
      if (LocaleCompare(expression,"QuantumScale") == 0)
        FxReturn(QuantumScale);
      break;
    }
    case 'R':
    case 'r':
    {
      if (IsFxFunction(expression,"rand",4) != MagickFalse)
        {
          double
            alpha;

#if defined(MAGICKCORE_OPENMP_SUPPORT)
          #pragma omp critical (MagickCore_FxEvaluateSubexpression)
#endif
          alpha=GetPseudoRandomValue(fx_info->random_info);
          FxReturn(alpha);
        }
      if (IsFxFunction(expression,"round",5) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+5,
            depth+1,beta,exception);
          if ((alpha-floor(alpha)) < (ceil(alpha)-alpha))
            FxReturn(floor(alpha));
          FxReturn(ceil(alpha));
        }
      if (LocaleCompare(expression,"r") == 0)
        FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,depth+1,exception));
      break;
    }
    case 'S':
    case 's':
    {
      if (LocaleCompare(expression,"saturation") == 0)
        FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,depth+1,exception));
      if (IsFxFunction(expression,"sign",4) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+4,
            depth+1,beta,exception);
          FxReturn(alpha < 0.0 ? -1.0 : 1.0);
        }
      if (IsFxFunction(expression,"sinc",4) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+4,
            depth+1,beta,exception);
          if (alpha == 0)
            FxReturn(1.0);
          FxReturn(sin((MagickPI*alpha))/(MagickPI*alpha));
        }
      if (IsFxFunction(expression,"sinh",4) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+4,
            depth+1,beta,exception);
          FxReturn(sinh(alpha));
        }
      if (IsFxFunction(expression,"sin",3) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,
            depth+1,beta,exception);
          FxReturn(sin(alpha));
        }
      if (IsFxFunction(expression,"sqrt",4) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+4,
            depth+1,beta,exception);
          FxReturn(sqrt(alpha));
        }
      if (IsFxFunction(expression,"squish",6) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+6,
            depth+1,beta,exception);
          FxReturn((1.0/(1.0+exp(-alpha))));
        }
      if (LocaleCompare(expression,"s") == 0)
        FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,depth+1,exception));
      break;
    }
    case 'T':
    case 't':
    {
      if (IsFxFunction(expression,"tanh",4) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+4,
            depth+1,beta,exception);
          FxReturn(tanh(alpha));
        }
      if (IsFxFunction(expression,"tan",3) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,
            depth+1,beta,exception);
          FxReturn(tan(alpha));
        }
      if (LocaleCompare(expression,"Transparent") == 0)
        FxReturn(0.0);
      if (IsFxFunction(expression,"trunc",5) != MagickFalse)
        {
          alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+5,
            depth+1,beta,exception);
          if (alpha >= 0.0)
            FxReturn(floor(alpha));
          FxReturn(ceil(alpha));
        }
      if (LocaleCompare(expression,"t") == 0)
        FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,depth+1,exception));
      break;
    }
    case 'U':
    case 'u':
    {
      if (LocaleCompare(expression,"u") == 0)
        FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,depth+1,exception));
      break;
    }
    case 'V':
    case 'v':
    {
      if (LocaleCompare(expression,"v") == 0)
        FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,depth+1,exception));
      break;
    }
    case 'W':
    case 'w':
    {
      if (IsFxFunction(expression,"while",5) != MagickFalse)
        {
          size_t
            length;

          /*
            Parse while(condition,expression).
          */
          length=CopyMagickString(subexpression,expression+6,
            MagickPathExtent-1);
          if (length != 0)
            subexpression[length-1]='\0';
          FxParseConditional(subexpression,',',p,q);
          for (alpha=0.0; ; )
          {
            gamma=FxEvaluateSubexpression(fx_info,channel,x,y,p,depth+1,beta,
              exception);
            if (fabs(gamma) < MagickEpsilon)
              break;
            alpha=FxEvaluateSubexpression(fx_info,channel,x,y,q+1,depth+1,beta,
              exception);
          }
          FxReturn(alpha);
        }
      if (LocaleCompare(expression,"w") == 0)
        FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,depth+1,exception));
      break;
    }
    case 'Y':
    case 'y':
    {
      if (LocaleCompare(expression,"y") == 0)
        FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,depth+1,exception));
      break;
    }
    case 'Z':
    case 'z':
    {
      if (LocaleCompare(expression,"z") == 0)
        FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,depth+1,exception));
      break;
    }
    default:
      break;
  }
  q=(char *) expression;
  alpha=InterpretSiPrefixValue(expression,&q);
  if (q == expression)
    alpha=FxGetSymbol(fx_info,channel,x,y,expression,depth+1,exception);
  if (*q == ')')
    (void) ThrowMagickException(exception,GetMagickModule(),OptionError,
      "UnbalancedParenthesis","`%s'",expression);
  FxReturn(alpha);
}

MagickExport MagickBooleanType FxEvaluateExpression(FxInfo *fx_info,
  double *alpha,ExceptionInfo *exception)
{
  MagickBooleanType
    status;

  status=FxEvaluateChannelExpression(fx_info,GrayChannel,0,0,alpha,exception);
  return(status);
}

MagickExport MagickBooleanType FxPreprocessExpression(FxInfo *fx_info,
  double *alpha,ExceptionInfo *exception)
{
  FILE
    *file;

  MagickBooleanType
    status;

  file=fx_info->file;
  fx_info->file=(FILE *) NULL;
  status=FxEvaluateChannelExpression(fx_info,GrayChannel,0,0,alpha,exception);
  fx_info->file=file;
  return(status);
}

MagickExport MagickBooleanType FxEvaluateChannelExpression(FxInfo *fx_info,
  const ChannelType channel,const ssize_t x,const ssize_t y,double *alpha,
  ExceptionInfo *exception)
{
  double
    beta;

  beta=0.0;
  *alpha=FxEvaluateSubexpression(fx_info,channel,x,y,fx_info->expression,0,
    &beta,exception);
  return(exception->severity == OptionError ? MagickFalse : MagickTrue);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%     F x I m a g e                                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  FxImage() applies a mathematical expression to the specified image.
%
%  The format of the FxImage method is:
%
%      Image *FxImage(const Image *image,const char *expression,
%        ExceptionInfo *exception)
%      Image *FxImageChannel(const Image *image,const ChannelType channel,
%        const char *expression,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image: the image.
%
%    o channel: the channel.
%
%    o expression: A mathematical expression.
%
%    o exception: return any errors or warnings in this structure.
%
*/

static FxInfo **DestroyFxTLS(FxInfo **fx_info)
{
  ssize_t
    i;

  assert(fx_info != (FxInfo **) NULL);
  for (i=0; i < (ssize_t) GetMagickResourceLimit(ThreadResource); i++)
    if (fx_info[i] != (FxInfo *) NULL)
      fx_info[i]=DestroyFxInfo(fx_info[i]);
  fx_info=(FxInfo **) RelinquishMagickMemory(fx_info);
  return(fx_info);
}

static FxInfo **AcquireFxTLS(const Image *image,const char *expression,
  ExceptionInfo *exception)
{
  char
    *fx_expression;

  double
    alpha;

  FxInfo
    **fx_info;

  ssize_t
    i;

  size_t
    number_threads;

  number_threads=(size_t) GetMagickResourceLimit(ThreadResource);
  fx_info=(FxInfo **) AcquireQuantumMemory(number_threads,sizeof(*fx_info));
  if (fx_info == (FxInfo **) NULL)
    {
      (void) ThrowMagickException(exception,GetMagickModule(),
        ResourceLimitError,"MemoryAllocationFailed","`%s'",image->filename);
      return((FxInfo **) NULL);
    }
  (void) memset(fx_info,0,number_threads*sizeof(*fx_info));
  if (*expression != '@')
    fx_expression=ConstantString(expression);
  else
    fx_expression=FileToString(expression,~0UL,exception);
  for (i=0; i < (ssize_t) number_threads; i++)
  {
    MagickBooleanType
      status;

    fx_info[i]=AcquireFxInfo(image,fx_expression);
    if (fx_info[i] == (FxInfo *) NULL)
      break;
    status=FxPreprocessExpression(fx_info[i],&alpha,exception);
    if (status == MagickFalse)
      break;
  }
  fx_expression=DestroyString(fx_expression);
  if (i < (ssize_t) number_threads)
    fx_info=DestroyFxTLS(fx_info);
  return(fx_info);
}

MagickExport Image *FxImage(const Image *image,const char *expression,
  ExceptionInfo *exception)
{
  Image
    *fx_image;

  fx_image=FxImageChannel(image,GrayChannel,expression,exception);
  return(fx_image);
}

MagickExport Image *FxImageChannel(const Image *image,const ChannelType channel,
  const char *expression,ExceptionInfo *exception)
{
#define FxImageTag  "Fx/Image"

  CacheView
    *fx_view;

  FxInfo
    **magick_restrict fx_info;

  Image
    *fx_image;

  MagickBooleanType
    status;

  MagickOffsetType
    progress;

  ssize_t
    y;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  if (expression == (const char *) NULL)
    return(CloneImage(image,0,0,MagickTrue,exception));
  fx_info=AcquireFxTLS(image,expression,exception);
  if (fx_info == (FxInfo **) NULL)
    return((Image *) NULL);
  fx_image=CloneImage(image,0,0,MagickTrue,exception);
  if (fx_image == (Image *) NULL)
    {
      fx_info=DestroyFxTLS(fx_info);
      return((Image *) NULL);
    }
  if (SetImageStorageClass(fx_image,DirectClass) == MagickFalse)
    {
      InheritException(exception,&fx_image->exception);
      fx_info=DestroyFxTLS(fx_info);
      fx_image=DestroyImage(fx_image);
      return((Image *) NULL);
    }
  /*
    Fx image.
  */
  status=MagickTrue;
  progress=0;
  fx_view=AcquireAuthenticCacheView(fx_image,exception);
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp parallel for schedule(dynamic) shared(progress,status) \
    magick_number_threads(image,fx_image,fx_image->rows, \
      GlobExpression(fx_info[0]->expression,"*debug(*",MagickTrue) == 0 ? 1 : 0)
#endif
  for (y=0; y < (ssize_t) fx_image->rows; y++)
  {
    const int
      id = GetOpenMPThreadId();

    double
      alpha;

    IndexPacket
      *magick_restrict fx_indexes;

    ssize_t
      x;

    PixelPacket
      *magick_restrict q;

    if (status == MagickFalse)
      continue;
    q=GetCacheViewAuthenticPixels(fx_view,0,y,fx_image->columns,1,exception);
    if (q == (PixelPacket *) NULL)
      {
        status=MagickFalse;
        continue;
      }
    fx_indexes=GetCacheViewAuthenticIndexQueue(fx_view);
    alpha=0.0;
    for (x=0; x < (ssize_t) fx_image->columns; x++)
    {
      if ((channel & RedChannel) != 0)
        {
          (void) FxEvaluateChannelExpression(fx_info[id],RedChannel,x,y,
            &alpha,exception);
          SetPixelRed(q,ClampToQuantum((MagickRealType) QuantumRange*alpha));
        }
      if ((channel & GreenChannel) != 0)
        {
          (void) FxEvaluateChannelExpression(fx_info[id],GreenChannel,x,y,
            &alpha,exception);
          SetPixelGreen(q,ClampToQuantum((MagickRealType) QuantumRange*alpha));
        }
      if ((channel & BlueChannel) != 0)
        {
          (void) FxEvaluateChannelExpression(fx_info[id],BlueChannel,x,y,
            &alpha,exception);
          SetPixelBlue(q,ClampToQuantum((MagickRealType) QuantumRange*alpha));
        }
      if ((channel & OpacityChannel) != 0)
        {
          (void) FxEvaluateChannelExpression(fx_info[id],OpacityChannel,x,y,
            &alpha,exception);
          if (image->matte == MagickFalse)
            SetPixelOpacity(q,ClampToQuantum((MagickRealType) QuantumRange*
              alpha));
          else
            SetPixelOpacity(q,ClampToQuantum((MagickRealType) QuantumRange-
              (MagickRealType) QuantumRange*alpha));
        }
      if (((channel & IndexChannel) != 0) &&
          (fx_image->colorspace == CMYKColorspace))
        {
          (void) FxEvaluateChannelExpression(fx_info[id],IndexChannel,x,y,
            &alpha,exception);
          SetPixelIndex(fx_indexes+x,ClampToQuantum((MagickRealType)
            QuantumRange*alpha));
        }
      q++;
    }
    if (SyncCacheViewAuthenticPixels(fx_view,exception) == MagickFalse)
      status=MagickFalse;
    if (image->progress_monitor != (MagickProgressMonitor) NULL)
      {
        MagickBooleanType
          proceed;

#if defined(MAGICKCORE_OPENMP_SUPPORT)
        #pragma omp atomic
#endif
        progress++;
        proceed=SetImageProgress(image,FxImageTag,progress,image->rows);
        if (proceed == MagickFalse)
          status=MagickFalse;
      }
  }
  fx_view=DestroyCacheView(fx_view);
  fx_info=DestroyFxTLS(fx_info);
  if (status == MagickFalse)
    fx_image=DestroyImage(fx_image);
  return(fx_image);
}
