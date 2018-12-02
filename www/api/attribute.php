



<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="utf-8" >
  <meta name="viewport" content="width=device-width,minimum-scale=1,initial-scale=1,shrink-to-fit=no" >
  <title>MagickCore, C API: Set Text Attributes @ ImageMagick</title>
  <meta name="application-name" content="ImageMagick">
  <meta name="description" content="Use ImageMagick® to create, edit, compose, convert bitmap images. With ImageMagick you can resize your image, crop it, change its shades and colors, add captions, among other operations.">
  <meta name="application-url" content="https://imagemagick.org">
  <meta name="generator" content="PHP">
  <meta name="keywords" content="magickcore, c, api:, set, text, attributes, ImageMagick, PerlMagick, image processing, image, photo, software, Magick++, OpenMP, convert">
  <meta name="rating" content="GENERAL">
  <meta name="robots" content="INDEX, FOLLOW">
  <meta name="generator" content="ImageMagick Studio LLC">
  <meta name="author" content="ImageMagick Studio LLC">
  <meta name="revisit-after" content="2 DAYS">
  <meta name="resource-type" content="document">
  <meta name="copyright" content="Copyright (c) 1999-2017 ImageMagick Studio LLC">
  <meta name="distribution" content="Global">
  <meta name="magick-serial" content="P131-S030410-R485315270133-P82224-A6668-G1245-1">
  <meta name="google-site-verification" content="_bMOCDpkx9ZAzBwb2kF3PRHbfUUdFj2uO8Jd1AXArz4">
  <link href="https://imagemagick.org/api/attribute.php" rel="canonical">
  <link href="../image/wand.png" rel="icon">
  <link href="../image/wand.ico" rel="shortcut icon">
  <link href="../assets/magick-css.php" rel="stylesheet">
</head>
<body>
  <header>
  <nav class="navbar navbar-expand-md navbar-dark bg-dark fixed-top">
    <a class="navbar-brand" href="../index.html"><img class="d-block" id="wand" alt="ImageMagick" width="32" height="32" src="../image/wand.ico"/></a>
    <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarsExampleDefault" aria-controls="navbarsExampleDefault" aria-expanded="false" aria-label="Toggle navigation">
      <span class="navbar-toggler-icon"></span>
    </button>

    <div class="navbar-collapse collapse" id="navbarsExampleDefault" style="">
    <ul class="navbar-nav mr-auto">
      <li class="nav-item ">
        <a class="nav-link" href="../index.php">Home <span class="sr-only">(current)</span></a>
      </li>
      <li class="nav-item ">
        <a class="nav-link" href="../script/download.php">Download</a>
      </li>
      <li class="nav-item ">
        <a class="nav-link" href="../script/command-line-tools.php">Tools</a>
      </li>
      <li class="nav-item ">
        <a class="nav-link" href="../script/command-line-processing.php">Command-line</a>
      </li>
      <li class="nav-item ">
        <a class="nav-link" href="../script/resources.php">Resources</a>
      </li>
      <li class="nav-item ">
        <a class="nav-link" href="../script/develop.php">Develop</a>
      </li>
      <li class="nav-item">
        <a class="nav-link" target="_blank" href="https://imagemagick.org/discourse-server/">Community</a>
      </li>
    </ul>
    <form class="form-inline my-2 my-lg-0" action="../script/search.php">
      <input class="form-control mr-sm-2" type="text" name="q" placeholder="Search" aria-label="Search">
      <button class="btn btn-outline-success my-2 my-sm-0" type="submit" name="sa">Search</button>
    </form>
    </div>
  </nav>
  <div class="container">
   <script async="async" src="https://pagead2.googlesyndication.com/pagead/js/adsbygoogle.js"></script>    <ins class="adsbygoogle"
         style="display:block"
         data-ad-client="ca-pub-3129977114552745"
         data-ad-slot="6345125851"
         data-ad-format="auto"></ins>
    <script>
      (adsbygoogle = window.adsbygoogle || []).push({});
    </script>
  </div>
  </header>
  <main class="container">
    <div class="magick-template">
<div class="magick-header">
<p class="text-center"><a href="attribute.php#GetImageChannelDepth">GetImageChannelDepth</a> &bull; <a href="attribute.php#GetImageQuantumDepth">GetImageQuantumDepth</a> &bull; <a href="attribute.php#GetImageType">GetImageType</a> &bull; <a href="attribute.php#IdentifyImageMonochrome">IdentifyImageMonochrome</a> &bull; <a href="attribute.php#IdentifyImageType">IdentifyImageType</a> &bull; <a href="attribute.php#IsGrayImage">IsGrayImage</a> &bull; <a href="attribute.php#IsMonochromeImage">IsMonochromeImage</a> &bull; <a href="attribute.php#IsOpaqueImage">IsOpaqueImage</a> &bull; <a href="attribute.php#SetImageChannelDepth">SetImageChannelDepth</a> &bull; <a href="attribute.php#SetImageType">SetImageType</a></p>

<h2><a href="https://imagemagick.org/api/MagickCore/attribute_8c.html" id="GetImageChannelDepth">GetImageChannelDepth</a></h2>

<p>GetImageChannelDepth() returns the depth of a particular image channel.</p>

<p>The format of the GetImageChannelDepth method is:</p>

<pre class="text">
size_t GetImageDepth(const Image *image,ExceptionInfo *exception)
size_t GetImageChannelDepth(const Image *image,
  const ChannelType channel,ExceptionInfo *exception)
</pre>

<p>A description of each parameter follows:</p>

<dd>
</dd>

<dd> </dd>
<dl class="dl-horizontal">
<dt>image</dt>
<dd>the image. </dd>

<dd> </dd>
<dt>channel</dt>
<dd>the channel. </dd>

<dd> </dd>
<dt>exception</dt>
<dd>return any errors or warnings in this structure. </dd>

<dd>  </dd>
</dl>
<h2><a href="https://imagemagick.org/api/MagickCore/attribute_8c.html" id="GetImageQuantumDepth">GetImageQuantumDepth</a></h2>

<p>GetImageQuantumDepth() returns the depth of the image rounded to a legal quantum depth: 8, 16, or 32.</p>

<p>The format of the GetImageQuantumDepth method is:</p>

<pre class="text">
size_t GetImageQuantumDepth(const Image *image,
  const MagickBooleanType constrain)
</pre>

<p>A description of each parameter follows:</p>

<dd>
</dd>

<dd> </dd>
<dl class="dl-horizontal">
<dt>image</dt>
<dd>the image. </dd>

<dd> </dd>
<dt>constrain</dt>
<dd>A value other than MagickFalse, constrains the depth to a maximum of MAGICKCORE_QUANTUM_DEPTH. </dd>

<dd>  </dd>
</dl>
<h2><a href="https://imagemagick.org/api/MagickCore/attribute_8c.html" id="GetImageType">GetImageType</a></h2>

<p>GetImageType() returns the potential type of image:</p>

<p>Bilevel         Grayscale        GrayscaleMatte Palette         PaletteMatte     TrueColor TrueColorMatte  ColorSeparation  ColorSeparationMatte</p>

<p>To ensure the image type matches its potential, use SetImageType():</p>

<pre class="text">
    (void) SetImageType(image,GetImageType(image));
</pre>

<p>The format of the GetImageType method is:</p>

<pre class="text">
ImageType GetImageType(const Image *image,ExceptionInfo *exception)
</pre>

<p>A description of each parameter follows:</p>

<dd>
</dd>

<dd> </dd>
<dl class="dl-horizontal">
<dt>image</dt>
<dd>the image. </dd>

<dd> </dd>
<dt>exception</dt>
<dd>return any errors or warnings in this structure. </dd>

<dd>  </dd>
</dl>
<h2><a href="https://imagemagick.org/api/MagickCore/attribute_8c.html" id="IdentifyImageMonochrome">IdentifyImageMonochrome</a></h2>

<p>IdentifyImageMonochrome() returns MagickTrue if all the pixels in the image have the same red, green, and blue intensities and the intensity is either 0 or QuantumRange.</p>

<p>The format of the IdentifyImageMonochrome method is:</p>

<pre class="text">
MagickBooleanType IdentifyImageMonochrome(const Image *image,
  ExceptionInfo *exception)
</pre>

<p>A description of each parameter follows:</p>

<dd>
</dd>

<dd> </dd>
<dl class="dl-horizontal">
<dt>image</dt>
<dd>the image. </dd>

<dd> </dd>
<dt>exception</dt>
<dd>return any errors or warnings in this structure. </dd>

<dd>  </dd>
</dl>
<h2><a href="https://imagemagick.org/api/MagickCore/attribute_8c.html" id="IdentifyImageType">IdentifyImageType</a></h2>

<p>IdentifyImageType() returns the potential type of image:</p>

<p>Bilevel         Grayscale        GrayscaleMatte Palette         PaletteMatte     TrueColor TrueColorMatte  ColorSeparation  ColorSeparationMatte</p>

<p>To ensure the image type matches its potential, use SetImageType():</p>

<pre class="text">
    (void) SetImageType(image,IdentifyImageType(image,exception),exception);
</pre>

<p>The format of the IdentifyImageType method is:</p>

<pre class="text">
ImageType IdentifyImageType(const Image *image,ExceptionInfo *exception)
</pre>

<p>A description of each parameter follows:</p>

<dd>
</dd>

<dd> </dd>
<dl class="dl-horizontal">
<dt>image</dt>
<dd>the image. </dd>

<dd> </dd>
<dt>exception</dt>
<dd>return any errors or warnings in this structure. </dd>

<dd>  </dd>
</dl>
<h2><a href="https://imagemagick.org/api/MagickCore/attribute_8c.html" id="IsGrayImage">IsGrayImage</a></h2>

<p>IsGrayImage() returns MagickTrue if the type of the image is grayscale or bi-level.</p>

<p>The format of the IsGrayImage method is:</p>

<pre class="text">
MagickBooleanType IsGrayImage(const Image *image,
  ExceptionInfo *exception)
</pre>

<p>A description of each parameter follows:</p>

<dd>
</dd>

<dd> </dd>
<dl class="dl-horizontal">
<dt>image</dt>
<dd>the image. </dd>

<dd> </dd>
<dt>exception</dt>
<dd>return any errors or warnings in this structure. </dd>

<dd>  </dd>
</dl>
<h2><a href="https://imagemagick.org/api/MagickCore/attribute_8c.html" id="IsMonochromeImage">IsMonochromeImage</a></h2>

<p>IsMonochromeImage() returns MagickTrue if type of the image is bi-level.</p>

<p>The format of the IsMonochromeImage method is:</p>

<pre class="text">
MagickBooleanType IsMonochromeImage(const Image *image,
  ExceptionInfo *exception)
</pre>

<p>A description of each parameter follows:</p>

<dd>
</dd>

<dd> </dd>
<dl class="dl-horizontal">
<dt>image</dt>
<dd>the image. </dd>

<dd> </dd>
<dt>exception</dt>
<dd>return any errors or warnings in this structure. </dd>

<dd>  </dd>
</dl>
<h2><a href="https://imagemagick.org/api/MagickCore/attribute_8c.html" id="IsOpaqueImage">IsOpaqueImage</a></h2>

<p>IsOpaqueImage() returns MagickTrue if none of the pixels in the image have an opacity value other than opaque (0).</p>

<p>The format of the IsOpaqueImage method is:</p>

<pre class="text">
MagickBooleanType IsOpaqueImage(const Image *image,
  ExceptionInfo *exception)
</pre>

<p>A description of each parameter follows:</p>

<dd>
</dd>

<dd> </dd>
<dl class="dl-horizontal">
<dt>image</dt>
<dd>the image. </dd>

<dd> </dd>
<dt>exception</dt>
<dd>return any errors or warnings in this structure. </dd>

<dd>  </dd>
</dl>
<h2><a href="https://imagemagick.org/api/MagickCore/attribute_8c.html" id="SetImageChannelDepth">SetImageChannelDepth</a></h2>

<p>SetImageChannelDepth() sets the depth of the image.</p>

<p>The format of the SetImageChannelDepth method is:</p>

<pre class="text">
MagickBooleanType SetImageDepth(Image *image,const size_t depth)
MagickBooleanType SetImageChannelDepth(Image *image,
  const ChannelType channel,const size_t depth)
</pre>

<p>A description of each parameter follows:</p>

<dd>
</dd>

<dd> </dd>
<dl class="dl-horizontal">
<dt>image</dt>
<dd>the image. </dd>

<dd> </dd>
<dt>channel</dt>
<dd>the channel. </dd>

<dd> </dd>
<dt>depth</dt>
<dd>the image depth. </dd>

<dd>  </dd>
</dl>
<h2><a href="https://imagemagick.org/api/MagickCore/attribute_8c.html" id="SetImageType">SetImageType</a></h2>

<p>SetImageType() sets the type of image.  Choose from these types:</p>

<p>BilevelType, GrayscaleType, GrayscaleMatteType, PaletteType, PaletteMatteType, TrueColorType, TrueColorMatteType, ColorSeparationType, ColorSeparationMatteType, OptimizeType</p>

<p>The format of the SetImageType method is:</p>

<pre class="text">
MagickBooleanType SetImageType(Image *image,const ImageType type)
</pre>

<p>A description of each parameter follows:</p>

<dd>
</dd>

<dd> </dd>
<dl class="dl-horizontal">
<dt>image</dt>
<dd>the image. </dd>

<dd> </dd>
<dt>type</dt>
<dd>Image type. </dd>

<dd>  </dd>
</dl>
</div>
    </div>
  </main><!-- /.container -->
  <footer class="magick-footer">
    <p><a href="../script/security-policy.php">Security</a> •
    <a href="../script/architecture.php">Architecture</a> •
    <a href="../script/links.php">Related</a> •
     <a href="../script/sitemap.php">Sitemap</a>
    &nbsp; &nbsp;
    <a href="attribute.php#"><img class="d-inline" id="wand" alt="And Now a Touch of Magick" width="16" height="16" src="../image/wand.ico"/></a>
    &nbsp; &nbsp;
    <a href="http://pgp.mit.edu/pks/lookup?op=get&amp;search=0x89AB63D48277377A">Public Key</a> •
    <a href="../script/support.php">Donate</a> •
    <a href="../script/contact.php">Contact Us</a>
    <br/>
        <small>© 1999-2019 ImageMagick Studio LLC</small></p>
  </footer>

  <!-- Javascript assets -->
  <script src="../assets/magick-js.php" crossorigin="anonymous"></script>
  <script>window.jQuery || document.write('<script src="../assets/jquery.min.js"><\/script>')</script>
</body>
</html>
