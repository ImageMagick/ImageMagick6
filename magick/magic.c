/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%                    M   M   AAA    GGGG  IIIII   CCCC                        %
%                    MM MM  A   A  G        I    C                            %
%                    M M M  AAAAA  G GGG    I    C                            %
%                    M   M  A   A  G   G    I    C                            %
%                    M   M  A   A   GGGG  IIIII   CCCC                        %
%                                                                             %
%                                                                             %
%                      MagickCore Image Magic Methods                         %
%                                                                             %
%                              Software Design                                %
%                              Bob Friesenhahn                                %
%                                 July 2000                                   %
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
*/

/*
  Include declarations.
*/
#include "magick/studio.h"
#include "magick/blob.h"
#include "magick/client.h"
#include "magick/configure.h"
#include "magick/exception.h"
#include "magick/exception-private.h"
#include "magick/hashmap.h"
#include "magick/magic.h"
#include "magick/memory_.h"
#include "magick/semaphore.h"
#include "magick/string_.h"
#include "magick/string-private.h"
#include "magick/token.h"
#include "magick/utility.h"
#include "magick/xml-tree.h"
#include "magick/xml-tree-private.h"

/*
  Define declarations.
*/
#define MagicFilename  "magic.xml"
#define MagicPattern(magic)  (const unsigned char *) (magic), sizeof(magic)-1

/*
  Typedef declarations.
*/
typedef struct _MagicMapInfo
{
  const char
    name[10];

  const MagickOffsetType
    offset;

  const unsigned char
    *const magic;

  const size_t
    length;
} MagicMapInfo;

/*
  Static declarations.
*/
static const MagicMapInfo
  MagicMap[] =
  {
    { "8BIMWTEXT", 0, MagicPattern("8\000B\000I\000M\000#") },
    { "8BIMTEXT", 0, MagicPattern("8BIM#") },
    { "8BIM", 0, MagicPattern("8BIM") },
    { "AVIF", 4, MagicPattern("ftypavif") },
    { "AVIF", 4, MagicPattern("ftypavis") },
    { "BMP", 0, MagicPattern("BA") },
    { "BMP", 0, MagicPattern("BM") },
    { "BMP", 0, MagicPattern("CI") },
    { "BMP", 0, MagicPattern("CP") },
    { "BMP", 0, MagicPattern("IC") },
    { "PICT", 0, MagicPattern("PICT") },
    { "BMP", 0, MagicPattern("PI") },
    { "CALS", 21, MagicPattern("version: MIL-STD-1840") },
    { "CALS", 0, MagicPattern("srcdocid:") },
    { "CALS", 9, MagicPattern("srcdocid:") },
    { "CALS", 8, MagicPattern("rorient:") },
    { "CGM", 0, MagicPattern("BEGMF") },
    { "CIN", 0, MagicPattern("\200\052\137\327") },
    { "CR2", 0, MagicPattern("II\x2a\x00\x10\x00\x00\x00CR\x02") },
    { "CR2", 0, MagicPattern("MM\x00\x2a\x00\x10\x00\x00RC\x02") },
    { "CRW", 0, MagicPattern("II\x1a\x00\x00\x00HEAPCCDR") },
    { "DCM", 128, MagicPattern("DICM") },
    { "DCX", 0, MagicPattern("\261\150\336\72") },
    { "DIB", 0, MagicPattern("\050\000") },
    { "DDS", 0, MagicPattern("DDS ") },
    { "DJVU", 0, MagicPattern("AT&TFORM") },
    { "DOT", 0, MagicPattern("digraph") },
    { "DPX", 0, MagicPattern("SDPX") },
    { "DPX", 0, MagicPattern("XPDS") },
    { "EMF", 40, MagicPattern("\040\105\115\106\000\000\001\000") },
    { "EPT", 0, MagicPattern("\305\320\323\306") },
    { "EXR", 0, MagicPattern("\166\057\061\001") },
    { "FAX", 0, MagicPattern("DFAX") },
    { "FIG", 0, MagicPattern("#FIG") },
    { "FITS", 0, MagicPattern("IT0") },
    { "FITS", 0, MagicPattern("SIMPLE") },
    { "FLIF", 0, MagicPattern("FLIF") },
    { "GIF", 0, MagicPattern("GIF8") },
    { "GPLT", 0, MagicPattern("#!/usr/local/bin/gnuplot") },
    { "HDF", 1, MagicPattern("HDF") },
    { "HDR", 0, MagicPattern("#?RADIANCE") },
    { "HDR", 0, MagicPattern("#?RGBE") },
    { "HEIC", 4, MagicPattern("ftypheic") },
    { "HEIC", 4, MagicPattern("ftypheix") },
    { "HEIC", 4, MagicPattern("ftyphevc") },
    { "HEIC", 4, MagicPattern("ftypheim") },
    { "HEIC", 4, MagicPattern("ftypheis") },
    { "HEIC", 4, MagicPattern("ftyphevm") },
    { "HEIC", 4, MagicPattern("ftyphevs") },
    { "HEIC", 4, MagicPattern("ftypmif1") },
    { "HEIC", 4, MagicPattern("ftypmsf1") },
    { "HPGL", 0, MagicPattern("IN;") },
    { "HTML", 1, MagicPattern("HTML") },
    { "HTML", 1, MagicPattern("html") },
    { "ILBM", 8, MagicPattern("ILBM") },
    { "IPTCWTEXT", 0, MagicPattern("\062\000#\000\060\000=\000\042\000&\000#\000\060\000;\000&\000#\000\062\000;\000\042\000") },
    { "IPTCTEXT", 0, MagicPattern("2#0=\042&#0;&#2;\042") },
    { "IPTC", 0, MagicPattern("\034\002") },
    { "JNG", 0, MagicPattern("\213JNG\r\n\032\n") },
    { "JPEG", 0, MagicPattern("\377\330\377") },
    { "J2K", 0, MagicPattern("\xff\x4f\xff\x51") },
    { "JPC", 0, MagicPattern("\x0d\x0a\x87\x0a") },
    { "JP2", 0, MagicPattern("\x00\x00\x00\x0c\x6a\x50\x20\x20\x0d\x0a\x87\x0a") },
    { "JXL", 0, MagicPattern("\xff\x0a") },
    { "JXL", 0, MagicPattern("\x00\x00\x00\x0c\x4a\x58\x4c\x20\x0d\x0a\x87\x0a") },
    { "MAT", 0, MagicPattern("MATLAB 5.0 MAT-file,") },
    { "MIFF", 0, MagicPattern("Id=ImageMagick") },
    { "MIFF", 0, MagicPattern("id=ImageMagick") },
    { "MNG", 0, MagicPattern("\212MNG\r\n\032\n") },
    { "MPC", 0, MagicPattern("id=MagickCache") },
    { "MPEG", 0, MagicPattern("\000\000\001\263") },
    { "MRW", 0, MagicPattern("\x00MRM") },
    { "ORF", 0, MagicPattern("IIRO\x08\x00\x00\x00") },
    { "PCD", 2048, MagicPattern("PCD_") },
    { "PCL", 0, MagicPattern("\033E\033") },
    { "PCX", 0, MagicPattern("\012\002") },
    { "PCX", 0, MagicPattern("\012\005") },
    { "PDB", 60, MagicPattern("vIMGView") },
    { "PDF", 0, MagicPattern("%PDF-") },
    { "PES", 0, MagicPattern("#PES") },
    { "PFA", 0, MagicPattern("%!PS-AdobeFont-1.0") },
    { "PFB", 6, MagicPattern("%!PS-AdobeFont-1.0") },
    { "PGX", 0, MagicPattern("PG ML") },
    { "PGX", 0, MagicPattern("PG LM") },
    { "PICT", 522, MagicPattern("\000\021\002\377\014\000") },
    { "PNG", 0, MagicPattern("\211PNG\r\n\032\n") },
    { "PBM", 0, MagicPattern("P1") },
    { "PGM", 0, MagicPattern("P2") },
    { "PPM", 0, MagicPattern("P3") },
    { "PBM", 0, MagicPattern("P4") },
    { "PGM", 0, MagicPattern("P5") },
    { "PPM", 0, MagicPattern("P6") },
    { "PAM", 0, MagicPattern("P7") },
    { "PFM", 0, MagicPattern("PF") },
    { "PFM", 0, MagicPattern("Pf") },
    { "PS", 0, MagicPattern("%!") },
    { "PS", 0, MagicPattern("\004%!") },
    { "PS", 0, MagicPattern("\305\320\323\306") },
    { "PSB", 0, MagicPattern("8BPB") },
    { "PSD", 0, MagicPattern("8BPS") },
    { "PWP", 0, MagicPattern("SFW95") },
    { "RAF", 0, MagicPattern("FUJIFILMCCD-RAW ") },
    { "RAW", 0, MagicPattern("IIU\x00\x08\x00\x00\x00") },
    { "RW2", 0, MagicPattern("IIU\x00\x18\x00\x00\x00") },
    { "RLE", 0, MagicPattern("\122\314") },
    { "SCT", 0, MagicPattern("CT") },
    { "SFW", 0, MagicPattern("SFW94") },
    { "SGI", 0, MagicPattern("\001\332") },
    { "SUN", 0, MagicPattern("\131\246\152\225") },
    { "SVG", 1, MagicPattern("?XML") },
    { "SVG", 1, MagicPattern("?xml") },
    { "SVG", 1, MagicPattern("SVG") },
    { "SVG", 1, MagicPattern("svg") },
    { "TIFF", 0, MagicPattern("\115\115\000\052") },
    { "TIFF", 0, MagicPattern("\111\111\052\000") },
    { "TIFF64", 0, MagicPattern("\115\115\000\053\000\010\000\000") },
    { "TIFF64", 0, MagicPattern("\111\111\053\000\010\000\000\000") },
    { "TTF", 0, MagicPattern("\000\001\000\000\000") },
    { "TXT", 0, MagicPattern("# ImageMagick pixel enumeration:") },
    { "VICAR", 0, MagicPattern("LBLSIZE") },
    { "VICAR", 0, MagicPattern("NJPL1I") },
    { "VIFF", 0, MagicPattern("\253\001") },
    { "WEBP", 8, MagicPattern("WEBP") },
    { "WMF", 0, MagicPattern("\327\315\306\232") },
    { "WMF", 0, MagicPattern("\001\000\011\000") },
    { "WPG", 0, MagicPattern("\377WPC") },
    { "XBM", 0, MagicPattern("#define") },
    { "XCF", 0, MagicPattern("gimp xcf") },
    { "XEF", 0, MagicPattern("FOVb") },
    { "XPM", 1, MagicPattern("* XPM *") }
 };

static LinkedListInfo
  *magic_cache = (LinkedListInfo *) NULL;

static SemaphoreInfo
  *magic_semaphore = (SemaphoreInfo *) NULL;

/*
  Forward declarations.
*/
static MagickBooleanType
  IsMagicCacheInstantiated(ExceptionInfo *);

#if !MAGICKCORE_ZERO_CONFIGURATION_SUPPORT
static MagickBooleanType
  LoadMagicCache(LinkedListInfo *,const char *,const char *,const size_t,
    ExceptionInfo *);
#endif

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%  A c q u i r e M a g i c C a c h e                                          %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  AcquireMagicCache() caches one or more magic configurations which provides a
%  mapping between magic attributes and a magic name.
%
%  The format of the AcquireMagicCache method is:
%
%      LinkedListInfo *AcquireMagicCache(const char *filename,
%        ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o filename: the font file name.
%
%    o exception: return any errors or warnings in this structure.
%
*/
static int CompareMagickInfoSize(const void *a,const void *b)
{
  MagicInfo
    *ma,
    *mb;

  ma=(MagicInfo *) a;
  mb=(MagicInfo *) b;
  if (ma->offset != mb->offset)
    return((int) (ma->offset-mb->offset));
  return((int) (mb->length-(ssize_t) ma->length));
}

static LinkedListInfo *AcquireMagicCache(const char *filename,
  ExceptionInfo *exception)
{
  LinkedListInfo
    *cache;

  MagickStatusType
    status;

  ssize_t
    i;

  cache=NewLinkedList(0);
  if (cache == (LinkedListInfo *) NULL)
    ThrowFatalException(ResourceLimitFatalError,"MemoryAllocationFailed");
  /*
    Load external magic map.
  */
  status=MagickTrue;
#if !MAGICKCORE_ZERO_CONFIGURATION_SUPPORT
  {
    char
      path[MaxTextExtent];

    const StringInfo
      *option;

    LinkedListInfo
      *options;

    *path='\0';
    options=GetConfigureOptions(filename,exception);
    option=(const StringInfo *) GetNextValueInLinkedList(options);
    while (option != (const StringInfo *) NULL)
    {
      (void) CopyMagickString(path,GetStringInfoPath(option),MaxTextExtent);
      status&=LoadMagicCache(cache,(const char *)
        GetStringInfoDatum(option),GetStringInfoPath(option),0,exception);
      option=(const StringInfo *) GetNextValueInLinkedList(options);
    }
    options=DestroyConfigureOptions(options);
  }
#endif
  /*
    Load built-in magic map.
  */
  for (i=0; i < (ssize_t) (sizeof(MagicMap)/sizeof(*MagicMap)); i++)
  {
    MagicInfo
      *magic_info;

    const MagicMapInfo
      *p;

    p=MagicMap+i;
    magic_info=(MagicInfo *) AcquireMagickMemory(sizeof(*magic_info));
    if (magic_info == (MagicInfo *) NULL)
      {
        (void) ThrowMagickException(exception,GetMagickModule(),
          ResourceLimitError,"MemoryAllocationFailed","`%s'",p->name);
        continue;
      }
    (void) memset(magic_info,0,sizeof(*magic_info));
    magic_info->path=(char *) "[built-in]";
    magic_info->name=(char *) p->name;
    magic_info->offset=p->offset;
    magic_info->target=(char *) p->magic;
    magic_info->magic=(unsigned char *) p->magic;
    magic_info->length=p->length;
    magic_info->exempt=MagickTrue;
    magic_info->signature=MagickCoreSignature;
    status&=InsertValueInSortedLinkedList(cache,CompareMagickInfoSize,
      NULL,magic_info);
    if (status == MagickFalse)
      (void) ThrowMagickException(exception,GetMagickModule(),
        ResourceLimitError,"MemoryAllocationFailed","`%s'",magic_info->name);
  }
  return(cache);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   G e t M a g i c I n f o                                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  GetMagicInfo() searches the magic list for the specified name and if found
%  returns attributes for that magic.
%
%  The format of the GetMagicInfo method is:
%
%      const MagicInfo *GetMagicInfo(const unsigned char *magic,
%        const size_t length,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o magic: A binary string generally representing the first few characters
%      of the image file or blob.
%
%    o length: the length of the binary signature.
%
%    o exception: return any errors or warnings in this structure.
%
*/
MagickExport const MagicInfo *GetMagicInfo(const unsigned char *magic,
  const size_t length,ExceptionInfo *exception)
{
  const MagicInfo
    *p;

  assert(exception != (ExceptionInfo *) NULL);
  if (IsMagicCacheInstantiated(exception) == MagickFalse)
    return((const MagicInfo *) NULL);
  /*
    Search for magic tag.
  */
  LockSemaphoreInfo(magic_semaphore);
  ResetLinkedListIterator(magic_cache);
  p=(const MagicInfo *) GetNextValueInLinkedList(magic_cache);
  if (magic == (const unsigned char *) NULL)
    {
      UnlockSemaphoreInfo(magic_semaphore);
      return(p);
    }
  while (p != (const MagicInfo *) NULL)
  {
    const unsigned char
      *q;

    MagickOffsetType
      remaining;

    assert(p->offset >= 0);
    q=magic+p->offset;
    remaining=(MagickOffsetType) length-p->offset;
    if (LocaleCompare(p->name,"SVG") == 0)
      while ((remaining > 0) && (isspace(*q) != 0))
      {
        q++;
        remaining--;
      }
    if ((remaining >= (MagickOffsetType) p->length) &&
        (memcmp(q,p->magic,p->length) == 0))
      break;
    p=(const MagicInfo *) GetNextValueInLinkedList(magic_cache);
  }
  if (p != (const MagicInfo *) NULL)
    (void) InsertValueInLinkedList(magic_cache,0,
      RemoveElementByValueFromLinkedList(magic_cache,p));
  UnlockSemaphoreInfo(magic_semaphore);
  return(p);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   G e t M a g i c I n f o L i s t                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  GetMagicInfoList() returns any image aliases that match the specified
%  pattern.
%
%  The magic of the GetMagicInfoList function is:
%
%      const MagicInfo **GetMagicInfoList(const char *pattern,
%        size_t *number_aliases,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o pattern: Specifies a pointer to a text string containing a pattern.
%
%    o number_aliases:  This integer returns the number of aliases in the list.
%
%    o exception: return any errors or warnings in this structure.
%
*/

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

static int MagicInfoCompare(const void *x,const void *y)
{
  const MagicInfo
    **p,
    **q;

  p=(const MagicInfo **) x,
  q=(const MagicInfo **) y;
  if (LocaleCompare((*p)->path,(*q)->path) == 0)
    return(LocaleCompare((*p)->name,(*q)->name));
  return(LocaleCompare((*p)->path,(*q)->path));
}

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

MagickExport const MagicInfo **GetMagicInfoList(const char *pattern,
  size_t *number_aliases,ExceptionInfo *exception)
{
  const MagicInfo
    **aliases;

  const MagicInfo
    *p;

  ssize_t
    i;

  /*
    Allocate magic list.
  */
  assert(pattern != (char *) NULL);
  assert(number_aliases != (size_t *) NULL);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",pattern);
  *number_aliases=0;
  p=GetMagicInfo((const unsigned char *) NULL,0,exception);
  if (p == (const MagicInfo *) NULL)
    return((const MagicInfo **) NULL);
  aliases=(const MagicInfo **) AcquireQuantumMemory((size_t)
    GetNumberOfElementsInLinkedList(magic_cache)+1UL,sizeof(*aliases));
  if (aliases == (const MagicInfo **) NULL)
    return((const MagicInfo **) NULL);
  /*
    Generate magic list.
  */
  LockSemaphoreInfo(magic_semaphore);
  ResetLinkedListIterator(magic_cache);
  p=(const MagicInfo *) GetNextValueInLinkedList(magic_cache);
  for (i=0; p != (const MagicInfo *) NULL; )
  {
    if ((p->stealth == MagickFalse) &&
        (GlobExpression(p->name,pattern,MagickFalse) != MagickFalse))
      aliases[i++]=p;
    p=(const MagicInfo *) GetNextValueInLinkedList(magic_cache);
  }
  UnlockSemaphoreInfo(magic_semaphore);
  qsort((void *) aliases,(size_t) i,sizeof(*aliases),MagicInfoCompare);
  aliases[i]=(MagicInfo *) NULL;
  *number_aliases=(size_t) i;
  return(aliases);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   G e t M a g i c L i s t                                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  GetMagicList() returns any image format aliases that match the specified
%  pattern.
%
%  The format of the GetMagicList function is:
%
%      char **GetMagicList(const char *pattern,size_t *number_aliases,
%        ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o pattern: Specifies a pointer to a text string containing a pattern.
%
%    o number_aliases:  This integer returns the number of image format aliases
%      in the list.
%
%    o exception: return any errors or warnings in this structure.
%
*/

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

static int MagicCompare(const void *x,const void *y)
{
  const char
    *p,
    *q;

  p=(const char *) x;
  q=(const char *) y;
  return(LocaleCompare(p,q));
}

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

MagickExport char **GetMagicList(const char *pattern,size_t *number_aliases,
  ExceptionInfo *exception)
{
  char
    **aliases;

  const MagicInfo
    *p;

  ssize_t
    i;

  /*
    Allocate configure list.
  */
  assert(pattern != (char *) NULL);
  assert(number_aliases != (size_t *) NULL);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",pattern);
  *number_aliases=0;
  p=GetMagicInfo((const unsigned char *) NULL,0,exception);
  if (p == (const MagicInfo *) NULL)
    return((char **) NULL);
  aliases=(char **) AcquireQuantumMemory((size_t)
    GetNumberOfElementsInLinkedList(magic_cache)+1UL,sizeof(*aliases));
  if (aliases == (char **) NULL)
    return((char **) NULL);
  LockSemaphoreInfo(magic_semaphore);
  ResetLinkedListIterator(magic_cache);
  p=(const MagicInfo *) GetNextValueInLinkedList(magic_cache);
  for (i=0; p != (const MagicInfo *) NULL; )
  {
    if ((p->stealth == MagickFalse) &&
        (GlobExpression(p->name,pattern,MagickFalse) != MagickFalse))
      aliases[i++]=ConstantString(p->name);
    p=(const MagicInfo *) GetNextValueInLinkedList(magic_cache);
  }
  UnlockSemaphoreInfo(magic_semaphore);
  qsort((void *) aliases,(size_t) i,sizeof(*aliases),MagicCompare);
  aliases[i]=(char *) NULL;
  *number_aliases=(size_t) i;
  return(aliases);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   G e t M a g i c N a m e                                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  GetMagicName() returns the name associated with the magic.
%
%  The format of the GetMagicName method is:
%
%      const char *GetMagicName(const MagicInfo *magic_info)
%
%  A description of each parameter follows:
%
%    o magic_info:  The magic info.
%
*/
MagickExport const char *GetMagicName(const MagicInfo *magic_info)
{
  assert(magic_info != (MagicInfo *) NULL);
  assert(magic_info->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"...");
  return(magic_info->name);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   I s M a g i c C a c h e I n s t a n t i a t e d                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  IsMagicCacheInstantiated() determines if the magic list is instantiated.
%  If not, it instantiates the list and returns it.
%
%  The format of the IsMagicInstantiated method is:
%
%      MagickBooleanType IsMagicCacheInstantiated(ExceptionInfo *exception)
%
%  A description of each parameter follows.
%
%    o exception: return any errors or warnings in this structure.
%
*/
static MagickBooleanType IsMagicCacheInstantiated(ExceptionInfo *exception)
{
  if (magic_cache == (LinkedListInfo *) NULL)
    {
      if (magic_semaphore == (SemaphoreInfo *) NULL)
        ActivateSemaphoreInfo(&magic_semaphore);
      LockSemaphoreInfo(magic_semaphore);
      if (magic_cache == (LinkedListInfo *) NULL)
        magic_cache=AcquireMagicCache(MagicFilename,exception);
      UnlockSemaphoreInfo(magic_semaphore);
    }
  return(magic_cache != (LinkedListInfo *) NULL ? MagickTrue : MagickFalse);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%  L i s t M a g i c I n f o                                                  %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  ListMagicInfo() lists the magic info to a file.
%
%  The format of the ListMagicInfo method is:
%
%      MagickBooleanType ListMagicInfo(FILE *file,ExceptionInfo *exception)
%
%  A description of each parameter follows.
%
%    o file:  An pointer to a FILE.
%
%    o exception: return any errors or warnings in this structure.
%
*/
MagickExport MagickBooleanType ListMagicInfo(FILE *file,
  ExceptionInfo *exception)
{
  const char
    *path;

  const MagicInfo
    **magic_info;

  ssize_t
    i;

  size_t
    number_aliases;

  ssize_t
    j;

  if (file == (const FILE *) NULL)
    file=stdout;
  magic_info=GetMagicInfoList("*",&number_aliases,exception);
  if (magic_info == (const MagicInfo **) NULL)
    return(MagickFalse);
  j=0;
  path=(const char *) NULL;
  for (i=0; i < (ssize_t) number_aliases; i++)
  {
    if (magic_info[i]->stealth != MagickFalse)
      continue;
    if ((path == (const char *) NULL) ||
        (LocaleCompare(path,magic_info[i]->path) != 0))
      {
        if (magic_info[i]->path != (char *) NULL)
          (void) FormatLocaleFile(file,"\nPath: %s\n\n",magic_info[i]->path);
        (void) FormatLocaleFile(file,"Name      Offset Target\n");
        (void) FormatLocaleFile(file,
          "-------------------------------------------------"
          "------------------------------\n");
      }
    path=magic_info[i]->path;
    (void) FormatLocaleFile(file,"%s",magic_info[i]->name);
    for (j=(ssize_t) strlen(magic_info[i]->name); j <= 9; j++)
      (void) FormatLocaleFile(file," ");
    (void) FormatLocaleFile(file,"%6ld ",(long) magic_info[i]->offset);
    if (magic_info[i]->target != (char *) NULL)
      {
        ssize_t
          j;

        for (j=0; magic_info[i]->target[j] != '\0'; j++)
          if (isprint((int) ((unsigned char) magic_info[i]->target[j])) != 0)
            (void) FormatLocaleFile(file,"%c",magic_info[i]->target[j]);
          else
            (void) FormatLocaleFile(file,"\\%03o",(unsigned int)
              ((unsigned char) magic_info[i]->target[j]));
      }
    (void) FormatLocaleFile(file,"\n");
  }
  (void) fflush(file);
  magic_info=(const MagicInfo **) RelinquishMagickMemory((void *) magic_info);
  return(MagickTrue);
}

#if !MAGICKCORE_ZERO_CONFIGURATION_SUPPORT
/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   L o a d M a g i c C a c h e                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  LoadMagicCache() loads the magic configurations which provides a mapping
%  between magic attributes and a magic name.
%
%  The format of the LoadMagicCache method is:
%
%      MagickBooleanType LoadMagicCache(LinkedListInfo *cache,const char *xml,
%        const char *filename,const size_t depth,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o xml: The magic list in XML format.
%
%    o filename: The magic list filename.
%
%    o depth: depth of <include /> statements.
%
%    o exception: return any errors or warnings in this structure.
%
*/
static MagickBooleanType LoadMagicCache(LinkedListInfo *cache,const char *xml,
  const char *filename,const size_t depth,ExceptionInfo *exception)
{
  char
    keyword[MaxTextExtent],
    *token;

  const char
    *q;

  MagicInfo
    *magic_info;

  MagickStatusType
    status;

  size_t
    extent;

  /*
    Load the magic map file.
  */
  (void) LogMagickEvent(ConfigureEvent,GetMagickModule(),
    "Loading magic configure file \"%s\" ...",filename);
  if (xml == (char *) NULL)
    return(MagickFalse);
  status=MagickTrue;
  magic_info=(MagicInfo *) NULL;
  token=AcquireString(xml);
  extent=strlen(token)+MaxTextExtent;
  for (q=(char *) xml; *q != '\0'; )
  {
    /*
      Interpret XML.
    */
    (void) GetNextToken(q,&q,extent,token);
    if (*token == '\0')
      break;
    (void) CopyMagickString(keyword,token,MaxTextExtent);
    if (LocaleNCompare(keyword,"<!DOCTYPE",9) == 0)
      {
        /*
          Doctype element.
        */
        while ((LocaleNCompare(q,"]>",2) != 0) && (*q != '\0'))
          (void) GetNextToken(q,&q,extent,token);
        continue;
      }
    if (LocaleNCompare(keyword,"<!--",4) == 0)
      {
        /*
          Comment element.
        */
        while ((LocaleNCompare(q,"->",2) != 0) && (*q != '\0'))
          (void) GetNextToken(q,&q,extent,token);
        continue;
      }
    if (LocaleCompare(keyword,"<include") == 0)
      {
        /*
          Include element.
        */
        while (((*token != '/') && (*(token+1) != '>')) && (*q != '\0'))
        {
          (void) CopyMagickString(keyword,token,MaxTextExtent);
          (void) GetNextToken(q,&q,extent,token);
          if (*token != '=')
            continue;
          (void) GetNextToken(q,&q,extent,token);
          if (LocaleCompare(keyword,"file") == 0)
            {
              if (depth > MagickMaxRecursionDepth)
                (void) ThrowMagickException(exception,GetMagickModule(),
                  ConfigureError,"IncludeElementNestedTooDeeply","`%s'",token);
              else
                {
                  char
                    path[MaxTextExtent],
                    *xml;

                  GetPathComponent(filename,HeadPath,path);
                  if (*path != '\0')
                    (void) ConcatenateMagickString(path,DirectorySeparator,
                      MaxTextExtent);
                  if (*token == *DirectorySeparator)
                    (void) CopyMagickString(path,token,MaxTextExtent);
                  else
                    (void) ConcatenateMagickString(path,token,MaxTextExtent);
                  xml=FileToXML(path,~0UL);
                  if (xml != (char *) NULL)
                    {
                      status&=LoadMagicCache(cache,xml,path,depth+1,
                        exception);
                      xml=(char *) RelinquishMagickMemory(xml);
                    }
                }
            }
        }
        continue;
      }
    if (LocaleCompare(keyword,"<magic") == 0)
      {
        /*
          Magic element.
        */
        magic_info=(MagicInfo *) AcquireMagickMemory(sizeof(*magic_info));
        if (magic_info == (MagicInfo *) NULL)
          ThrowFatalException(ResourceLimitFatalError,"MemoryAllocationFailed");
        (void) memset(magic_info,0,sizeof(*magic_info));
        magic_info->path=ConstantString(filename);
        magic_info->exempt=MagickFalse;
        magic_info->signature=MagickCoreSignature;
        continue;
      }
    if (magic_info == (MagicInfo *) NULL)
      continue;
    if ((LocaleCompare(keyword,"/>") == 0) ||
        (LocaleCompare(keyword,"</policy>") == 0))
      {
        status=AppendValueToLinkedList(cache,magic_info);
        if (status == MagickFalse)
          (void) ThrowMagickException(exception,GetMagickModule(),
            ResourceLimitError,"MemoryAllocationFailed","`%s'",
            magic_info->name);
        magic_info=(MagicInfo *) NULL;
        continue;
      }
    (void) GetNextToken(q,(const char **) NULL,extent,token);
    if (*token != '=')
      continue;
    (void) GetNextToken(q,&q,extent,token);
    (void) GetNextToken(q,&q,extent,token);
    switch (*keyword)
    {
      case 'N':
      case 'n':
      {
        if (LocaleCompare((char *) keyword,"name") == 0)
          {
            magic_info->name=ConstantString(token);
            break;
          }
        break;
      }
      case 'O':
      case 'o':
      {
        if (LocaleCompare((char *) keyword,"offset") == 0)
          {
            magic_info->offset=(MagickOffsetType) StringToLong(token);
            break;
          }
        break;
      }
      case 'S':
      case 's':
      {
        if (LocaleCompare((char *) keyword,"stealth") == 0)
          {
            magic_info->stealth=IsMagickTrue(token);
            break;
          }
        break;
      }
      case 'T':
      case 't':
      {
        if (LocaleCompare((char *) keyword,"target") == 0)
          {
            char
              *p;

            unsigned char
              *q;

            size_t
              length;

            length=strlen(token);
            magic_info->target=ConstantString(token);
            magic_info->magic=(unsigned char *) ConstantString(token);
            q=magic_info->magic;
            for (p=magic_info->target; *p != '\0'; )
            {
              if (*p == '\\')
                {
                  p++;
                  if (isdigit((int) ((unsigned char) *p)) != 0)
                    {
                      char
                        *end;

                      *q++=(unsigned char) strtol(p,&end,8);
                      p+=(ptrdiff_t) (end-p);
                      magic_info->length++;
                      continue;
                    }
                  switch (*p)
                  {
                    case 'b': *q='\b'; break;
                    case 'f': *q='\f'; break;
                    case 'n': *q='\n'; break;
                    case 'r': *q='\r'; break;
                    case 't': *q='\t'; break;
                    case 'v': *q='\v'; break;
                    case 'a': *q='a'; break;
                    case '?': *q='\?'; break;
                    default: *q=(unsigned char) (*p); break;
                  }
                  p++;
                  q++;
                  magic_info->length++;
                  continue;
                }
              else
                if (LocaleNCompare(p,"&amp;",5) == 0)
                  (void) CopyMagickString(p+1,p+5,length-magic_info->length);
              *q++=(unsigned char) (*p++);
              magic_info->length++;
            }
            break;
          }
        break;
      }
      default:
        break;
    }
  }
  token=(char *) RelinquishMagickMemory(token);
  return(status != 0 ? MagickTrue : MagickFalse);
}
#endif

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   M a g i c C o m p o n e n t G e n e s i s                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  MagicComponentGenesis() instantiates the magic component.
%
%  The format of the MagicComponentGenesis method is:
%
%      MagickBooleanType MagicComponentGenesis(void)
%
*/
MagickExport MagickBooleanType MagicComponentGenesis(void)
{
  if (magic_semaphore == (SemaphoreInfo *) NULL)
    magic_semaphore=AllocateSemaphoreInfo();
  return(MagickTrue);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   M a g i c C o m p o n e n t T e r m i n u s                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  MagicComponentTerminus() destroys the magic component.
%
%  The format of the MagicComponentTerminus method is:
%
%      MagicComponentTerminus(void)
%
*/

static void *DestroyMagicElement(void *magic_info)
{
  MagicInfo
    *p;

  p=(MagicInfo *) magic_info;
  if (p->exempt == MagickFalse)
    {
      if (p->path != (char *) NULL)
        p->path=DestroyString(p->path);
      if (p->name != (char *) NULL)
        p->name=DestroyString(p->name);
      if (p->target != (char *) NULL)
        p->target=DestroyString(p->target);
      if (p->magic != (unsigned char *) NULL)
        p->magic=(unsigned char *) RelinquishMagickMemory(p->magic);
    }
  p=(MagicInfo *) RelinquishMagickMemory(p);
  return((void *) NULL);
}

MagickExport void MagicComponentTerminus(void)
{
  if (magic_semaphore == (SemaphoreInfo *) NULL)
    ActivateSemaphoreInfo(&magic_semaphore);
  LockSemaphoreInfo(magic_semaphore);
  if (magic_cache != (LinkedListInfo *) NULL)
    magic_cache=DestroyLinkedList(magic_cache,DestroyMagicElement);
  UnlockSemaphoreInfo(magic_semaphore);
  DestroySemaphoreInfo(&magic_semaphore);
}
