# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [6.9.12-60](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-59...6.9.12-60) - 2022-07-31

### Commits

- beta release [`93a4cb0`](https://github.com/ImageMagick/ImageMagick6/commit/93a4cb0925af6d5bd79e14719d9ff89c513e8418)
- beta release [`70b8287`](https://github.com/ImageMagick/ImageMagick6/commit/70b8287f15f46490d0e6a82f45704f8f4d67699a)
- omp_init_lock() has undefined behavior if the lock is already init'ed @ https://github.com/ImageMagick/ImageMagick/issues/5360 [`43ef18f`](https://github.com/ImageMagick/ImageMagick6/commit/43ef18f86967560c42bced0b9bbcf9cfb8578edd)
- conditionally destroy mutex [`063fbba`](https://github.com/ImageMagick/ImageMagick6/commit/063fbba0b08da3f5d41688bd5dfaa6722899436d)
- lock/unlock mutex assumes an initialized lock [`d978c4f`](https://github.com/ImageMagick/ImageMagick6/commit/d978c4fceb32159034f67db14824937d21d7cca4)
- fix -evaluate Pow 2 issue @ https://github.com/ImageMagick/ImageMagick/issues/5376 [`a723ba4`](https://github.com/ImageMagick/ImageMagick6/commit/a723ba462ffac5414c0a4556479782507c7454f7)
- cosmetic [`3ceef61`](https://github.com/ImageMagick/ImageMagick6/commit/3ceef61345cc8a119dcff5eb13da7a7c891854d0)
- remove uneccessary signature check [`847c4d6`](https://github.com/ImageMagick/ImageMagick6/commit/847c4d6aec929fbc4effab5d5df4841c0af71868)
- remove unneccessary variable [`65bd30e`](https://github.com/ImageMagick/ImageMagick6/commit/65bd30ea06861a7f94f31ebc506b539d4310f631)
- eliminate compiler issues / warnings [`23cccb5`](https://github.com/ImageMagick/ImageMagick6/commit/23cccb5fd4a51638734248451a27d0ee78b20f6a)
- fix cast from provenance-free integer type to pointer type @ https://github.com/ImageMagick/ImageMagick/discussions/5380 [`d289c00`](https://github.com/ImageMagick/ImageMagick6/commit/d289c006ff87efd5263a3976b94829ee0877ed3d)
- ... [`41a1701`](https://github.com/ImageMagick/ImageMagick6/commit/41a1701c024487ddc24b29003142cca806d016c4)
- authenticate distributed cache [`aacc6df`](https://github.com/ImageMagick/ImageMagick6/commit/aacc6dff2217d7f8581795d2932fc340abcd2597)
- eliminate compiler warning [`f3abf56`](https://github.com/ImageMagick/ImageMagick6/commit/f3abf56d494ec139fe8136935cbe2b1e734b9d86)
- divide NCC by the # of channels @ https://github.com/dlemstra/Magick.NET/issues/1220 [`b487617`](https://github.com/ImageMagick/ImageMagick6/commit/b4876171e49c97aaea52b3e8bbbdb071c9c433ab)
- release [`2e15d53`](https://github.com/ImageMagick/ImageMagick6/commit/2e15d53ddf34934cdbbc8dea86c0812e04f17bfb)
- improve distributed cache exception messages [`71fdec1`](https://github.com/ImageMagick/ImageMagick6/commit/71fdec19252c3c409349a89984f7869c5e11f8a5)
- release [`2cabb26`](https://github.com/ImageMagick/ImageMagick6/commit/2cabb261cdcbce931754c0ff87101123ab052d9b)

## [6.9.12-59](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-58...6.9.12-59) - 2022-07-24

### Commits

- beta release [`ecc4153`](https://github.com/ImageMagick/ImageMagick6/commit/ecc4153d3c8998a073e0781b13c11e421933e081)
- beta release [`e6947fa`](https://github.com/ImageMagick/ImageMagick6/commit/e6947fa6a7cacb9b0dc3dcebf9635c6dd151307f)
- respect configure's --disable-assert option [`521d343`](https://github.com/ImageMagick/ImageMagick6/commit/521d343a6016f4a7d8ee8c6eb902427f67c6981b)
- disable assert in ImageMagick specific header [`daae430`](https://github.com/ImageMagick/ImageMagick6/commit/daae430bb05ec03b91bedaecf069d6ec561a339b)
- Added extra checks to make sure we don't go out of bounds when checking spaces. [`427d089`](https://github.com/ImageMagick/ImageMagick6/commit/427d089dd191cdb431ca8405ee84eb5057512fa3)
- eliminate a double free per [`dcb6e1e`](https://github.com/ImageMagick/ImageMagick6/commit/dcb6e1ecacf99993d649cf97d7a29ef876ed3a1d)
- fix quoting for autoconf sendfile check [`897170a`](https://github.com/ImageMagick/ImageMagick6/commit/897170a24e8501d4aaebe251069b80678c417401)
- check for drawing primitive boundaries to prevent overflow [`95a6cc3`](https://github.com/ImageMagick/ImageMagick6/commit/95a6cc383f7249fe23822d52e1a87ebe0102b7ff)
- eliminate unitialized warning [`8eba5c8`](https://github.com/ImageMagick/ImageMagick6/commit/8eba5c8564d366256bc8481995ec8ca2602d2364)
- open blob before checking dimensions to avoid memory leak in [`feb6f92`](https://github.com/ImageMagick/ImageMagick6/commit/feb6f9228dd9dc9a06ed6847a2ccb151c80bf9d5)
- reset alpha channel on pattern coder @ https://github.com/ImageMagick/ImageMagick/discussions/5331 [`2abe2b0`](https://github.com/ImageMagick/ImageMagick6/commit/2abe2b0b804eaaa4648dc9dcd0a0d709a0511d7a)
- release [`a814e68`](https://github.com/ImageMagick/ImageMagick6/commit/a814e6814b7bd4c5ac975e1df4d199b6fdf5435e)
- add svg:decode to list of built-in delegates [`58ad458`](https://github.com/ImageMagick/ImageMagick6/commit/58ad45805c9c59eb80b85716eb0ba02f14b43c29)
- normalize enhancement is equivalent to -contrast-stretch 2x1% [`c478579`](https://github.com/ImageMagick/ImageMagick6/commit/c478579a28522c5fbda4a0c6ee68815bbd54bddb)
- release [`c007bb9`](https://github.com/ImageMagick/ImageMagick6/commit/c007bb9cb5e9ac28a013826c8a8827a3e537f2ca)
- release [`9a003dc`](https://github.com/ImageMagick/ImageMagick6/commit/9a003dce6b409637d4543cbd6647a6d2dc4db4e9)
- its okay for index pointer to be null @ https://github.com/ImageMagick/ImageMagick6/issues/191 [`7172b47`](https://github.com/ImageMagick/ImageMagick6/commit/7172b4756d43931af939ff34825377514fc2758c)
- release [`813e7ca`](https://github.com/ImageMagick/ImageMagick6/commit/813e7ca2e75c43ba32c3bf2ac2f9ff5111443553)

## [6.9.12-58](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-57...6.9.12-58) - 2022-07-09

### Commits

- beta release [`1da2b52`](https://github.com/ImageMagick/ImageMagick6/commit/1da2b52a3629ea0daa9a8af4f28b61b6c6bff4ba)
- release [`87fef5a`](https://github.com/ImageMagick/ImageMagick6/commit/87fef5a8217b52ee69af81ec9742fa362b53e776)
- beta release [`a63a9cd`](https://github.com/ImageMagick/ImageMagick6/commit/a63a9cdc0c4d9eaf112604404e71307b1170f0c0)
- release [`a085128`](https://github.com/ImageMagick/ImageMagick6/commit/a0851283f88ec0bc825804898a162b7d854d12dd)

## [6.9.12-57](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-56...6.9.12-57) - 2022-07-09

### Commits

- beta release [`5f44691`](https://github.com/ImageMagick/ImageMagick6/commit/5f44691a5bf010a322ca661374aaf57dbc95ef70)
- Added extra check because the flag was removed in 0.21-Beta1. [`09e6bf8`](https://github.com/ImageMagick/ImageMagick6/commit/09e6bf834fe3d8468d4d54931c8b17fa9a2f6258)
- release [`748e502`](https://github.com/ImageMagick/ImageMagick6/commit/748e502545cf4ab802757dd43a03fb5619b4dae2)

## [6.9.12-56](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-55...6.9.12-56) - 2022-07-06

### Commits

- beta release [`e304c92`](https://github.com/ImageMagick/ImageMagick6/commit/e304c92801d940c593169e903acb3761f04e3038)
- preserve input depth @ https://github.com/ImageMagick/ImageMagick6/issues/188 [`7dd14de`](https://github.com/ImageMagick/ImageMagick6/commit/7dd14de86de68f4ce88a23691ff30a91607e5894)
- forgot semicolon [`a3da7e2`](https://github.com/ImageMagick/ImageMagick6/commit/a3da7e24a5774fc76405e802fd835a414751b3f6)
- fix "inner" trim issue @ https://github.com/ImageMagick/ImageMagick6/issues/187 [`097f297`](https://github.com/ImageMagick/ImageMagick6/commit/097f2973146cdf14d0802b0f9cffa29d57303581)
- update to latest automake/autoconf release [`a2ebfb6`](https://github.com/ImageMagick/ImageMagick6/commit/a2ebfb639361961bb7344c875f8c6dfbd121ccaf)
- recognize SVG file if it starts with whitespace @ https://github.com/ImageMagick/ImageMagick/issues/5294 [`0b2e1b6`](https://github.com/ImageMagick/ImageMagick6/commit/0b2e1b6afc869c6517db08307aab54b6e8ec5824)
- correct space detection algorithm [`09917a5`](https://github.com/ImageMagick/ImageMagick6/commit/09917a59ca776976f5b630eec28dff7fa0c9032c)
- avoid OMP deadlock @ https://github.com/ImageMagick/ImageMagick/issues/5301 [`82e46b9`](https://github.com/ImageMagick/ImageMagick6/commit/82e46b9dd3f089a21c2f16633d3fb26657ccb1dc)
- release [`4d9149f`](https://github.com/ImageMagick/ImageMagick6/commit/4d9149f16c60fea0445ad99fdcd682a3dc754139)

## [6.9.12-55](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-54...6.9.12-55) - 2022-07-03

### Commits

- beta release [`e76b0f8`](https://github.com/ImageMagick/ImageMagick6/commit/e76b0f83395178375fbd35280f453a6c40ac825c)
- beta release [`d1d0a38`](https://github.com/ImageMagick/ImageMagick6/commit/d1d0a38df6f3770651f2c2ae37801ea9c4a8c8c9)
- prevent undefined-shift [`b962233`](https://github.com/ImageMagick/ImageMagick6/commit/b962233bfde5bdf7b2b8b3e06b00873056cc70f1)
- prevent possible buffer overrun [`4393e83`](https://github.com/ImageMagick/ImageMagick6/commit/4393e83230128de1cb798b67e798101d683380b1)
- We need to remove the stream ourselves when the call to FT_Open_Face fails. [`518a834`](https://github.com/ImageMagick/ImageMagick6/commit/518a834efdbfb1ab22d98d6495494f141b051b9a)
- Added missing call to DestroyString. [`5141d76`](https://github.com/ImageMagick/ImageMagick6/commit/5141d76e2044edfdb3ff117253e8d10461571d82)
- Fixed registry lookup because GhostScript now also writes the patch version to the registry. [`e1703af`](https://github.com/ImageMagick/ImageMagick6/commit/e1703afb9fd998c059b5e5de69823b11584c7fbb)
- Added extra malloc method to avoid early calls to the policy checks on Windows that causes #185. [`cbc47f3`](https://github.com/ImageMagick/ImageMagick6/commit/cbc47f3fb6cb2386fae8f085166e7758a2d7d4d3)
- Removed defines. [`2bdd8d0`](https://github.com/ImageMagick/ImageMagick6/commit/2bdd8d07e07d21eb39a1869d39da1b8ad52fc6c3)
- Only check for dll's in non static build. [`df3c026`](https://github.com/ImageMagick/ImageMagick6/commit/df3c0266e7cb0634e95de32da1bc3a1b03ce8be4)
- Set the client name and path earlier. [`3a6003e`](https://github.com/ImageMagick/ImageMagick6/commit/3a6003ef52fecd163eb05d8253d233d88d0898f4)
- update issues link [`7f248bd`](https://github.com/ImageMagick/ImageMagick6/commit/7f248bd0672e129798e7567c0a7bf5cdd732b87b)
- fix background opacity rounding @ https://github.com/ImageMagick/ImageMagick/issues/5264 [`ecf097c`](https://github.com/ImageMagick/ImageMagick6/commit/ecf097c0825f62f22ba65aab0821405932913b02)
- regression in support of MPEG video after coder name-change to "video" @ https://github.com/ImageMagick/ImageMagick6/issues/181 [`931d1fe`](https://github.com/ImageMagick/ImageMagick6/commit/931d1fe27a594797fff6bb7631e2a03a65b74bf8)
- cosmetic [`fa2c9a4`](https://github.com/ImageMagick/ImageMagick6/commit/fa2c9a46c1e5ebbea3e45ebdd2867d5e527b48a0)
- Also check extension to fix possible stack overflow. [`f0a0274`](https://github.com/ImageMagick/ImageMagick6/commit/f0a0274919a9de07b090c75c34952df510a8c4bd)
- eliminate possible buffer overflow [`2b4eabb`](https://github.com/ImageMagick/ImageMagick6/commit/2b4eabb9d09b278f16727c635e928bd951c58773)
- set group 4 photometric to min-is-white [`877b4dc`](https://github.com/ImageMagick/ImageMagick6/commit/877b4dc4efe10a56199914340ce8fad129d4897f)
- dasharray requires non-zero values [`dda0dcc`](https://github.com/ImageMagick/ImageMagick6/commit/dda0dccb56bf811d1043e29c8d46f92eb43d07cb)
- eliminate compiler warning [`7615041`](https://github.com/ImageMagick/ImageMagick6/commit/7615041cb424617643406fbf0a7040af541c1b12)
- restrict rows/columns to one keyword [`5dcfcf4`](https://github.com/ImageMagick/ImageMagick6/commit/5dcfcf47520a62f908f14d073e3ad902be0ae4c4)
- revert [`8872179`](https://github.com/ImageMagick/ImageMagick6/commit/8872179aad3797098e6964de094ab23e974826ef)
- eliminate uninitialized value warning [`46ee067`](https://github.com/ImageMagick/ImageMagick6/commit/46ee067255c778c53fbb02d019c772c1374528b1)
- port Dirk's version 7 patches to draw.c [`1b9ea43`](https://github.com/ImageMagick/ImageMagick6/commit/1b9ea43c03df4ea4af5f31b24d33a11d9f04b1d5)
- eliminate compiler warning [`349a176`](https://github.com/ImageMagick/ImageMagick6/commit/349a1761c161414ed274eb384dade7c669d2719c)
- eliminate compiler warning [`a59642a`](https://github.com/ImageMagick/ImageMagick6/commit/a59642ab57c44482242fe896eeb9941568cba9d9)
- fix scrambled image @ https://github.com/ImageMagick/ImageMagick/issues/5291 [`15e1459`](https://github.com/ImageMagick/ImageMagick6/commit/15e14592c54d8fcf80586b403b05b033ee865620)
- yikes, misspelled 'length' [`2061c9c`](https://github.com/ImageMagick/ImageMagick6/commit/2061c9c8abbf64e872e5dc067ea6c950ce2cd0b3)
- release [`77717cb`](https://github.com/ImageMagick/ImageMagick6/commit/77717cb8fbc6ea944db357ec8efa23ad283bfcf0)

## [6.9.12-54](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-53...6.9.12-54) - 2022-06-20

### Commits

- beta release [`a31b89a`](https://github.com/ImageMagick/ImageMagick6/commit/a31b89a3f0d848a73b52842e00b0693c2ce5e0e8)
- release [`0509015`](https://github.com/ImageMagick/ImageMagick6/commit/05090154b9ea16c895b84698b202d71867d48add)

## [6.9.12-53](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-52...6.9.12-53) - 2022-06-19

### Commits

- beta release [`2b152c1`](https://github.com/ImageMagick/ImageMagick6/commit/2b152c1243264b25b44c515ca95fa1827aeee423)
- update DOX config files [`d332de8`](https://github.com/ImageMagick/ImageMagick6/commit/d332de8a9943699cbb25e18d5105276367591260)
- update DOX config files [`d628017`](https://github.com/ImageMagick/ImageMagick6/commit/d6280179903bcc156a57e60560ed5c6d0ca68dac)
- update DOX config files [`45110c5`](https://github.com/ImageMagick/ImageMagick6/commit/45110c554e99e81d965d943aac55cdc5ef42d02f)
- only check the shred count once [`6d3db6f`](https://github.com/ImageMagick/ImageMagick6/commit/6d3db6f94b16458b82bfc3774fc107f1ec00a356)
- cosmetic [`8e90ab0`](https://github.com/ImageMagick/ImageMagick6/commit/8e90ab0d47a47e07b34c745dd1db6e91a6cedefc)
- cosmetic [`1671346`](https://github.com/ImageMagick/ImageMagick6/commit/1671346143f77ea68519497dcbf2e6070b915f72)
- system:shred value has precedence over MAGICK_SHRED_PASSES [`a29777d`](https://github.com/ImageMagick/ImageMagick6/commit/a29777d26b4bb6ba4f7824009e1b6f266c639177)
- support shredding memory pools [`e5dbbb0`](https://github.com/ImageMagick/ImageMagick6/commit/e5dbbb0afac0a615320530f9f7988d091d80b916)
- update memory pointer [`ea8c73a`](https://github.com/ImageMagick/ImageMagick6/commit/ea8c73a05b78af7590c604b57322637ff2bf2828)
- first pass is fast for performance, second is crytographically strong [`15e729e`](https://github.com/ImageMagick/ImageMagick6/commit/15e729edcd033360a3d16df8f5974c79f4bdeac5)
- recommend shred value of 1 for performance reasons [`4fe06ac`](https://github.com/ImageMagick/ImageMagick6/commit/4fe06ac897047d4e2e573b08015d084190c95cac)
- only set the # of shred passes one time [`fc9746a`](https://github.com/ImageMagick/ImageMagick6/commit/fc9746a351acbd3139b8446722d15e8ff42f15ba)
- if enabled, shred streams [`2987085`](https://github.com/ImageMagick/ImageMagick6/commit/2987085994d9d8aa1a2c9d92b061c4ce2c3437f4)
- unmap mapped pixels [`5316839`](https://github.com/ImageMagick/ImageMagick6/commit/531683946155f1029876852e6b251f685773c02a)
- default mapped member to false [`79d9c6c`](https://github.com/ImageMagick/ImageMagick6/commit/79d9c6c0c7e9cf2f119fa24cdc6ee1095b4a1223)
- don't shred streaming pixels [`bdd30a8`](https://github.com/ImageMagick/ImageMagick6/commit/bdd30a819918bf6f72619433d03f874bf2c5de4b)
- rework shred passes [`24d66bd`](https://github.com/ImageMagick/ImageMagick6/commit/24d66bdf3e46cf44c58f9ace9a6bde133714a6e1)
- optimize performance [`975e715`](https://github.com/ImageMagick/ImageMagick6/commit/975e715e7cc652e0a6b244cead2724a12539223a)
- eliminate compiler warning [`4466926`](https://github.com/ImageMagick/ImageMagick6/commit/4466926fd4c52d335c3b13aaee8e737f6ae8b286)
- eliminate lint warnings [`af4e64c`](https://github.com/ImageMagick/ImageMagick6/commit/af4e64ce504b84d9504043495d35edd8113f8965)
- eliminate lint warnings [`f200174`](https://github.com/ImageMagick/ImageMagick6/commit/f200174d88b0791d60333f20bcd8913c4d79d5a4)
- support date:timestamp property [`cf7dc08`](https://github.com/ImageMagick/ImageMagick6/commit/cf7dc08636a7679fbdfac7a8f7d4af0f78708578)
- eliminate lint warnings [`4f34e8d`](https://github.com/ImageMagick/ImageMagick6/commit/4f34e8d6deea256c93cabde03775c0b452a03627)
- get timestamp from image-&gt;timestamp member [`5694940`](https://github.com/ImageMagick/ImageMagick6/commit/5694940303da237c8db39b61e278ace408cbf55c)
- eliminate lint warnings [`31d21ce`](https://github.com/ImageMagick/ImageMagick6/commit/31d21ce2b1759bc0c9bcdadf9477e04d4866ca4f)
- support registry:precision define [`31c7d05`](https://github.com/ImageMagick/ImageMagick6/commit/31c7d05623682a99ba83cce14e6b7a399e3d7e18)
- need at least one policy defined [`0f0e899`](https://github.com/ImageMagick/ImageMagick6/commit/0f0e89934bd82a6768bbb8fc0dcf9eb07c52cb87)
- eliminate lint warnings [`1498305`](https://github.com/ImageMagick/ImageMagick6/commit/14983052ab96d4d738480f4e4b1b210f33a70d42)
- eliminate compiler warning [`e3595eb`](https://github.com/ImageMagick/ImageMagick6/commit/e3595ebb4b8633dc76f912706429ff8c4eed449b)
- eliminate compiler warning [`145440f`](https://github.com/ImageMagick/ImageMagick6/commit/145440f0f4c265f13691cf97780a17c218503e05)
- eliminate lint warning [`909d770`](https://github.com/ImageMagick/ImageMagick6/commit/909d77066640baf07e01932b6aa5c719c50f1ccd)
- eliminate lint warnings [`eb27aca`](https://github.com/ImageMagick/ImageMagick6/commit/eb27aca292079c8f5f7c279029c71a6ff7da5fa0)
- eliminate lint warnings [`649b0e8`](https://github.com/ImageMagick/ImageMagick6/commit/649b0e8cfd4926aec5cc7cc0c0c06ca76c364611)
- note, system:precision is deprecated [`28e2fd5`](https://github.com/ImageMagick/ImageMagick6/commit/28e2fd51dd88e0f4367b3b28cd51421c9f20ef64)
- eliminate icc compiler warnings [`6e68635`](https://github.com/ImageMagick/ImageMagick6/commit/6e6863533a0faef62c6b2d601712dfbe0dbb992a)
- Reverted incorrect patch when doing auto-orient of an image that is right-top or left-bottom. [`9e0d7b9`](https://github.com/ImageMagick/ImageMagick6/commit/9e0d7b9aca687ec2b278fa9e0137f404a3e8d99a)
- Only close the file blob when gzopen is successful. [`c5fb917`](https://github.com/ImageMagick/ImageMagick6/commit/c5fb917d4454185c7b65961a4b7ae3c74d03c87d)
- Added method to add utf8 support for gzopen on Windows. [`70c6500`](https://github.com/ImageMagick/ImageMagick6/commit/70c6500391b17560b06ae3d4eebfe6a42e1efb09)
- Only parse SOURCE_DATE_EPOCH once. [`cab56c5`](https://github.com/ImageMagick/ImageMagick6/commit/cab56c5265ea8724fb93d04fcf0ca514df1147da)
- Restored check that did not seem to be necessary. [`f12a028`](https://github.com/ImageMagick/ImageMagick6/commit/f12a028a8e597ab6a4bfcaaeb0834bc805a5052a)
- Fixed copy paste mistake. [`5f5830b`](https://github.com/ImageMagick/ImageMagick6/commit/5f5830bebcd415025460fe2b22118a44b4b3dd7f)
- Also fix incorrect fclose for bzlib. [`429a7e7`](https://github.com/ImageMagick/ImageMagick6/commit/429a7e7775e1a60bda2eb1fd68d0b9f8b0fcfc2c)
- perl_vendorarch is not longer defined [`1afd0cd`](https://github.com/ImageMagick/ImageMagick6/commit/1afd0cd42aeb1cfd0de2da91835962e9a0ea3dd6)
- fix improper close when opening zipped file [`01e6075`](https://github.com/ImageMagick/ImageMagick6/commit/01e6075a17537504d5074579d6f4de61995ea9be)
- Restored setting the file to NULL. [`21240ae`](https://github.com/ImageMagick/ImageMagick6/commit/21240ae99b822b242ce9f52ce741ced7fe3cf656)
- release [`2bc6b3c`](https://github.com/ImageMagick/ImageMagick6/commit/2bc6b3cbbbab34458ff51b5332e313385c7ae5ef)

## [6.9.12-52](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-51...6.9.12-52) - 2022-06-05

### Commits

- release [`e27754a`](https://github.com/ImageMagick/ImageMagick6/commit/e27754aed20fed12e1e5f6e7159f083947130f3c)
- don't keep in repo [`51c8fe2`](https://github.com/ImageMagick/ImageMagick6/commit/51c8fe2c68340d8be7a69d54b40e633a61b37aa4)
- beta release [`f7e9c8c`](https://github.com/ImageMagick/ImageMagick6/commit/f7e9c8c49c43fbcb0fc88f63c7c608a4054bd4e0)
- Set pass when webp:target-size or webp:target-psnr are set. [`f182990`](https://github.com/ImageMagick/ImageMagick6/commit/f182990d0b9d455d67eee01013171b5eb74afc37)
- check for zero-length blobs [`b92fb01`](https://github.com/ImageMagick/ImageMagick6/commit/b92fb01a9a7cc7f66c5f66cc19760c6db2b4b921)
- cosmetic [`0f58c10`](https://github.com/ImageMagick/ImageMagick6/commit/0f58c10811ec7dbe8ba6d31943c554fc06715794)
- Move case statement to make sure that non FloatingPointQuantumFormat will end up in the default case. [`9f248ff`](https://github.com/ImageMagick/ImageMagick6/commit/9f248ff8266aa4a88007dff558d937bd149ffa52)
- Revert to previous commit because the ImageMagick 7 verion of this file was commited by accident. [`872cc9a`](https://github.com/ImageMagick/ImageMagick6/commit/872cc9aa4bdefd04ec66b5022d79af0e2ed96b18)
- Check for zero-length blobs. [`43a7b02`](https://github.com/ImageMagick/ImageMagick6/commit/43a7b02e5ec90a6cdb990968047d26594886020d)
- Added dependabot configuration. [`9413045`](https://github.com/ImageMagick/ImageMagick6/commit/9413045a999b7ae579eaa934ef69bdc542eec7dd)
- Corrected rotation angle for right-top and left-bottom in auto-orient. [`d4ef5f8`](https://github.com/ImageMagick/ImageMagick6/commit/d4ef5f8e4e92440907091cba05e7cb9c75e1156c)
- Bump actions/upload-artifact from 1 to 3 [`bd10637`](https://github.com/ImageMagick/ImageMagick6/commit/bd10637c5dc2d8379febac3e5b17167c89c4e856)
- Bump github/codeql-action from 1 to 2 [`8b0e990`](https://github.com/ImageMagick/ImageMagick6/commit/8b0e990fd560cc982e55351226ac2048a8a9af2f)
- release [`d04b5b0`](https://github.com/ImageMagick/ImageMagick6/commit/d04b5b056b916bea1f032e24f49350fe6970787c)

## [6.9.12-51](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-50...6.9.12-51) - 2022-05-30

### Commits

- beta release [`c4073a5`](https://github.com/ImageMagick/ImageMagick6/commit/c4073a51fdacfaf26781b4aaac39e4751e11adef)
- return previous value when FX statement is null [`d6cb74d`](https://github.com/ImageMagick/ImageMagick6/commit/d6cb74d5e3f970bcb66ed49515eec02ab05ecbae)
- Corrected pragma comments due to repository renames. [`1b57081`](https://github.com/ImageMagick/ImageMagick6/commit/1b57081dfc4084118f55482e37ccad12c21d6d22)
- latest ImageMagick documentation [`68a8ce1`](https://github.com/ImageMagick/ImageMagick6/commit/68a8ce12a4bcef69799d8a9a5cf1cd7ad790d520)
- release [`e89c04d`](https://github.com/ImageMagick/ImageMagick6/commit/e89c04d318562790ea6afc45c73c8d3a8e2ea123)

## [6.9.12-50](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-49...6.9.12-50) - 2022-05-16

### Commits

- beta release [`2225cde`](https://github.com/ImageMagick/ImageMagick6/commit/2225cde3e76dbe3f1aa4cba8f4fcc3c92c2fc229)
- fix temporary file leak [`6e3cf33`](https://github.com/ImageMagick/ImageMagick6/commit/6e3cf33cac68acdadff6ce03a9d88b485c8725b0)
- release [`8bb9411`](https://github.com/ImageMagick/ImageMagick6/commit/8bb9411cd08da1cfdd68f3f9b88007202e5464ff)

## [6.9.12-49](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-48...6.9.12-49) - 2022-05-15

### Merged

- Fix various redefinition warnings in mingw [`#180`](https://github.com/ImageMagick/ImageMagick6/pull/180)
- Fix build with -Werror [`#177`](https://github.com/ImageMagick/ImageMagick6/pull/177)

### Commits

- beta release [`3f25da1`](https://github.com/ImageMagick/ImageMagick6/commit/3f25da103a2139e41d282183b8ffde22e4f09946)
- PDF to PBM no longer returning all white @ https://github.com/ImageMagick/ImageMagick/issues/5134 [`53e7f93`](https://github.com/ImageMagick/ImageMagick6/commit/53e7f93869d6975a29d0868b2b05713d691bc755)
- Test with mingw-w64 using MSYS2 CI [`05a2e00`](https://github.com/ImageMagick/ImageMagick6/commit/05a2e0039414285f36512aa38dccc632593b56d5)
- autotools: Add ws2_32 library with MagickCore for Win32 platform [`2798c67`](https://github.com/ImageMagick/ImageMagick6/commit/2798c671a8754c7efae3d9d717e48897012144f1)
- eliminate compiler warnings [`21ffed7`](https://github.com/ImageMagick/ImageMagick6/commit/21ffed7d95ab949dcdc52ee683dc0965ffd99719)
- latest autoconf/automake config [`1481259`](https://github.com/ImageMagick/ImageMagick6/commit/148125937c46616879d0fb9b59d3a699718e09d5)
- automake/autoconf update [`12bcac5`](https://github.com/ImageMagick/ImageMagick6/commit/12bcac5d47b3d0b04b15cfbbe3af28a68028cd2b)
- automake/autoconf update [`4f055aa`](https://github.com/ImageMagick/ImageMagick6/commit/4f055aa73cf8e6b6bf8e267edd040d4a82e2f08d)
- correct check for Magick++ compliance [`beb34e1`](https://github.com/ImageMagick/ImageMagick6/commit/beb34e12c70a588f16b2d57b6809d7ef85b1a733)
- automake/autoconf remove obselete macros [`e0f009a`](https://github.com/ImageMagick/ImageMagick6/commit/e0f009a8af2f6cddcf5e03e271522422a83462a7)
- set AC_PREREQ() macro [`9192794`](https://github.com/ImageMagick/ImageMagick6/commit/919279480b7e069731dbfd9eef228ede0a7431f0)
- build RPM tweaks [`520c45a`](https://github.com/ImageMagick/ImageMagick6/commit/520c45ae1753d431989cb2de169a7d6698212c53)
- tweak BZIP2 autoconf macro [`ba96c74`](https://github.com/ImageMagick/ImageMagick6/commit/ba96c74c25047731c4257db87f782d87cde883aa)
- release [`d468e47`](https://github.com/ImageMagick/ImageMagick6/commit/d468e47a8edf9c787d97b36064ae17953dfedffa)

## [6.9.12-48](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-47...6.9.12-48) - 2022-05-07

### Commits

- beta release [`79631d0`](https://github.com/ImageMagick/ImageMagick6/commit/79631d042400c496843378ed0196a4b406c4250d)
- eliminate Coverity defect [`7f9f7af`](https://github.com/ImageMagick/ImageMagick6/commit/7f9f7af4df7ae0c520c06dd607f2c4ca75f4ef23)
- eliminate Coverity defect [`65ed243`](https://github.com/ImageMagick/ImageMagick6/commit/65ed243183b20224e724b57df4988bde1b64800f)
- possible memory leak @ https://github.com/ImageMagick/ImageMagick/issues/5121 [`ca7744c`](https://github.com/ImageMagick/ImageMagick6/commit/ca7744c2cd37b11a6a0abe50761aee178027c724)
- conditional logging [`a34e365`](https://github.com/ImageMagick/ImageMagick6/commit/a34e36577496414d2f36c1e491166b72c223dcab)
- release [`d28a02b`](https://github.com/ImageMagick/ImageMagick6/commit/d28a02b076d222169f299dbaa4377f74ae071ec0)

## [6.9.12-47](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-46...6.9.12-47) - 2022-04-30

### Commits

- prep Beta release [`4731b11`](https://github.com/ImageMagick/ImageMagick6/commit/4731b113f0b6d52574ded6c97e54d90a771534d7)
- possible obscure memory leak [`3414d5d`](https://github.com/ImageMagick/ImageMagick6/commit/3414d5dad69969bff4c1377ff58a9df892c6ff6b)
- check event mask before logging [`89f4f49`](https://github.com/ImageMagick/ImageMagick6/commit/89f4f49abdfbd8bc4db32a5f47d9ac32e75df7cd)
- check event mask before logging [`ffff75a`](https://github.com/ImageMagick/ImageMagick6/commit/ffff75a362f35e5112d7bb526c4b33dd6001263f)
- Stop using %GITHUB_WORKSPACE%. [`eed696f`](https://github.com/ImageMagick/ImageMagick6/commit/eed696f455d499f489280995754724ba2f508423)
- Use version 3 of checkout. [`35b49b1`](https://github.com/ImageMagick/ImageMagick6/commit/35b49b1523ab6f2db2dc2903137fe5b5f202e52b)
- Create ChangeLog during the release and daily build. [`47600c7`](https://github.com/ImageMagick/ImageMagick6/commit/47600c7aee4a05f70910c1d46ce21371f243c148)
- Removed ChangeLog.md because we now use the generated one. [`7d85c33`](https://github.com/ImageMagick/ImageMagick6/commit/7d85c334fa9f05105b536af7f3ff5074da3e6a8f)
- Use date of latest change to m4/version.m4 instead. [`cdbb330`](https://github.com/ImageMagick/ImageMagick6/commit/cdbb330ac35dbb1c74a1c83c1b4b59aeedd1fe43)
- The default fetch-depth is 1. [`b23e10c`](https://github.com/ImageMagick/ImageMagick6/commit/b23e10c380cc24687523d2073de6a929a5f464f0)
- improve/optimize logging [`78395b3`](https://github.com/ImageMagick/ImageMagick6/commit/78395b3affd854ff8aa349e42767202d30f574a0)
- squash compuler warning [`6546dc8`](https://github.com/ImageMagick/ImageMagick6/commit/6546dc84eb4097aa82584350858f4d1d94292b8d)
- https://github.com/ImageMagick/ImageMagick/issues/5041 [`2d820fc`](https://github.com/ImageMagick/ImageMagick6/commit/2d820fc2d05aae8e508b11930c5a6b8a496033ae)
- need Changelog.md, referenced by web pages [`58d7b69`](https://github.com/ImageMagick/ImageMagick6/commit/58d7b69e46ec0139669ce73e23b2c1b3a0bd8d5c)
- latest autoconf update [`d74b07a`](https://github.com/ImageMagick/ImageMagick6/commit/d74b07a1e3b4710272ad1980b1697f2f821ab196)
- latest automake update [`9c892ad`](https://github.com/ImageMagick/ImageMagick6/commit/9c892ade2b5bf5daa4e4d07f77c0938a9cb0cd14)
- moved to website repo [`6e57f76`](https://github.com/ImageMagick/ImageMagick6/commit/6e57f765651744dabc51bb4966ccc33af3ef790c)
- optimize thumbnail resizing [`94e60b2`](https://github.com/ImageMagick/ImageMagick6/commit/94e60b24e2497693f1f799b9cf522a0c566234c3)
- revert [`969d70d`](https://github.com/ImageMagick/ImageMagick6/commit/969d70da1c478a69a6d1a30f3c171a7c8d68c812)
- endian_support should be set to true. [`c5a96e0`](https://github.com/ImageMagick/ImageMagick6/commit/c5a96e05be9dc735514d14fe81364b7310212e78)
- Sort commits by date instead. [`185002f`](https://github.com/ImageMagick/ImageMagick6/commit/185002f9227fafe944bc80a2f5f96f23761abc55)
- check for image width/height exceeding INT_MAX [`1fc9d67`](https://github.com/ImageMagick/ImageMagick6/commit/1fc9d6719844e28d9f54e9ad7ffd7e255425ac44)
- eliminate compiler exception [`78e03e7`](https://github.com/ImageMagick/ImageMagick6/commit/78e03e75320121770f9fe77da2dada58df1099bf)
- possible divide by zero [`ea5d25b`](https://github.com/ImageMagick/ImageMagick6/commit/ea5d25b3193ac568d1acd84c3e29ce0695640965)
- more informative exception message [`6a08233`](https://github.com/ImageMagick/ImageMagick6/commit/6a082331cc12f3c870bd78f5d1528b42d1313031)
- optimize logging [`3b18a98`](https://github.com/ImageMagick/ImageMagick6/commit/3b18a98dfb1e614a7a95716b8629326e4901318a)
- eliminate compiler exception [`5ab10bb`](https://github.com/ImageMagick/ImageMagick6/commit/5ab10bb85af2185525dda18e60d0a9482843319e)
- eliminate compiler warning [`7bd8a5c`](https://github.com/ImageMagick/ImageMagick6/commit/7bd8a5cc9be042f4134d9abbb094f921bd3e71f9)
- eliminate compiler exception [`2eba158`](https://github.com/ImageMagick/ImageMagick6/commit/2eba15828209d58ed289821faa79b76be1eb3a25)
- release [`9198dc5`](https://github.com/ImageMagick/ImageMagick6/commit/9198dc51522ac061e56ce0fc2c94a2712038aba4)

## [6.9.12-46](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-45...6.9.12-46) - 2022-04-23

### Commits

- https://github.com/ImageMagick/ImageMagick/issues/4973 [`629154d`](https://github.com/ImageMagick/ImageMagick6/commit/629154d99c33e09c35ed0e2cb147212c5425b6b1)
- bump revision [`657c75f`](https://github.com/ImageMagick/ImageMagick6/commit/657c75f5e25acc6c8e269b704d5ea4e9bec451e7)
- eliminate compiler warning [`ef19c70`](https://github.com/ImageMagick/ImageMagick6/commit/ef19c70f68fa38a7fef0b71b43ccc30708679e94)
- release commits [`3857531`](https://github.com/ImageMagick/ImageMagick6/commit/38575313683062227601929340acf05ceb308150)
- eliminate Coverity defects [`c5c4515`](https://github.com/ImageMagick/ImageMagick6/commit/c5c451591974b4ca4835fd394c5f1da4da6fed11)
- eliminate Coverity defect [`5051477`](https://github.com/ImageMagick/ImageMagick6/commit/50514778fd451dba26ce4bcd821e6dcac0cb702a)
- latest autoconf/automake updates [`4370511`](https://github.com/ImageMagick/ImageMagick6/commit/43705112b251248d1e23bd527fd6e13a8d8e5774)
- Added option to mark the version as beta. [`2f967eb`](https://github.com/ImageMagick/ImageMagick6/commit/2f967ebc78b66a4723d501f5e0f33f82c03952d9)
- Changed triggers for the release build. [`049e01c`](https://github.com/ImageMagick/ImageMagick6/commit/049e01cdae1adef16f9d0da2afc6731dec7606c5)
- Updated .gitignore. [`0c7d4be`](https://github.com/ImageMagick/ImageMagick6/commit/0c7d4bef12ef6499892dfd19f09a9b3c4735d4e2)
- latest autoconf update [`40c0b2c`](https://github.com/ImageMagick/ImageMagick6/commit/40c0b2c432494dcbef76db431913d5095af14dbb)
- fix rare but possible memory leak [`20b1c9f`](https://github.com/ImageMagick/ImageMagick6/commit/20b1c9f59f986c6bd62ccf89736c47cebf4c6e87)
- set threshold policy by default [`5053b93`](https://github.com/ImageMagick/ImageMagick6/commit/5053b9399eae366224843b43085598ee5e2749da)
- encourage Unicode default font [`6c68a06`](https://github.com/ImageMagick/ImageMagick6/commit/6c68a0605bc97a723e48e3b44eae0fbd50ce70c2)
- update website [`a4ec146`](https://github.com/ImageMagick/ImageMagick6/commit/a4ec14613f8693b2ee8279a70b7ca591b1ffc5dd)
- release [`2346033`](https://github.com/ImageMagick/ImageMagick6/commit/2346033ebb1bb76f7cdd04276a96397e4b436bb9)

## [6.9.12-45](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-44...6.9.12-45) - 2022-04-16

### Commits

- prep next release [`df41269`](https://github.com/ImageMagick/ImageMagick6/commit/df41269a8f39e276a0da4c5a2ad1bfc7e938c506)
- do not set ICC properties unless the value is non-null [`5988721`](https://github.com/ImageMagick/ImageMagick6/commit/598872147bfb031a7d24749d8d1b9216e5153582)
- eliminate arbitrary limit on CMS descriptions [`2c452fc`](https://github.com/ImageMagick/ImageMagick6/commit/2c452fcffdf5d0a66287b5c89a7f7f0c721e8582)
- Removed unused assignment. [`44f42c2`](https://github.com/ImageMagick/ImageMagick6/commit/44f42c2521de1f8de17a87ac89d2345235071527)
- Improved freetype error reporting. [`05d5d26`](https://github.com/ImageMagick/ImageMagick6/commit/05d5d26f6cce099ba2e43c727144bac7b303087e)
- Added missing version check. [`93bbd3a`](https://github.com/ImageMagick/ImageMagick6/commit/93bbd3a26b9de035f2578eed05db3896f418ac12)
- Revert local check. [`8126c53`](https://github.com/ImageMagick/ImageMagick6/commit/8126c53d6793c702c960e32731ea08dedf7ba5b5)
- Corrected check. [`17aa89f`](https://github.com/ImageMagick/ImageMagick6/commit/17aa89f702a61cb9aa6026eec0739e3e3ae23661)
- check for empty string not needed [`cbbcfa1`](https://github.com/ImageMagick/ImageMagick6/commit/cbbcfa180ac7c06cd518d2d7ab8d0eb2e22b50f1)
- check to see if ICC property exists before its created [`a5263ab`](https://github.com/ImageMagick/ImageMagick6/commit/a5263ab3e463729adfe714cf1435430e84995672)
- revert [`354943b`](https://github.com/ImageMagick/ImageMagick6/commit/354943bd85df291c82e74650ae007f2af1f5b2da)
- do not permit setting read-only properties (e.g. exif:*) [`98abe54`](https://github.com/ImageMagick/ImageMagick6/commit/98abe54e6b54b4cfeef90ea7a5943cf453b680a3)
- https://github.com/ImageMagick/ImageMagick/pull/5034 [`dc070da`](https://github.com/ImageMagick/ImageMagick6/commit/dc070da861a015d3c97488fdcca6063b44d47a7b)
- https://github.com/ImageMagick/ImageMagick/issues/5028 [`6dca9a7`](https://github.com/ImageMagick/ImageMagick6/commit/6dca9a7c5c99d416e86605220970f3b85064e4a6)
- https://github.com/ImageMagick/ImageMagick/issues/5027 [`6f7a9e2`](https://github.com/ImageMagick/ImageMagick6/commit/6f7a9e23d816478c0dcccea32d38cef4ab517019)
- pending release [`e8700b9`](https://github.com/ImageMagick/ImageMagick6/commit/e8700b9d02223d6e0e47c792ee293bf1989fd024)
- eliminate compiler warning [`8ca2579`](https://github.com/ImageMagick/ImageMagick6/commit/8ca2579216dfbcb3a576ae1876dd8ac9ad68edae)
- future: throw an exception if type cache cannot be acquired [`ae21b8c`](https://github.com/ImageMagick/ImageMagick6/commit/ae21b8c554681a9884a572341ea55419a51f7da1)
- eliminate Coverity defects [`dcc7a67`](https://github.com/ImageMagick/ImageMagick6/commit/dcc7a6748c41c11a7926a4af6ac18f4ceccd48e5)
- https://github.com/ImageMagick/ImageMagick/issues/5037 [`1eb8339`](https://github.com/ImageMagick/ImageMagick6/commit/1eb8339661a982ff8a1cb82f0da34fe0931afc44)
- eliminate Coverity defects [`d6ccd35`](https://github.com/ImageMagick/ImageMagick6/commit/d6ccd350830317daf252202b5daf37e8c7e19678)
- eliminate Coverity defects [`5923cb3`](https://github.com/ImageMagick/ImageMagick6/commit/5923cb343f5787e814b3bc49880b739b08ee9399)
- streaming interface must be allocated on the heap [`f2ab27b`](https://github.com/ImageMagick/ImageMagick6/commit/f2ab27b2279e982ade0d29ceaf418b3c53d3b34a)
- fix memory leak in Freetype stream [`8ead70f`](https://github.com/ImageMagick/ImageMagick6/commit/8ead70f34a83ec16c7e346c3fb105e226b27b229)
- eliminate Coverity defects [`3d50253`](https://github.com/ImageMagick/ImageMagick6/commit/3d5025390e29252b9ca9fadd43e53956b0e3e43e)
- revert [`f49d606`](https://github.com/ImageMagick/ImageMagick6/commit/f49d606db5b3b0e6a45e5fab05ef17bdf047efbf)
- revert [`8c9e882`](https://github.com/ImageMagick/ImageMagick6/commit/8c9e882635e2dad22f9bfa41b82161b1aaebd0bb)
- eliminate Coverity defect [`c64edf6`](https://github.com/ImageMagick/ImageMagick6/commit/c64edf606451d522298a4cd172d9cb652236663d)
- utilitze fstat() blocksize to set stream buffer size [`7462d84`](https://github.com/ImageMagick/ImageMagick6/commit/7462d84b7bc6076522d2763a3d507429642666df)
- revert [`65b99c4`](https://github.com/ImageMagick/ImageMagick6/commit/65b99c4dc37287a8f8c2f264da22f0066da75626)
- eliminate compiler warning [`f82bd6a`](https://github.com/ImageMagick/ImageMagick6/commit/f82bd6a040f159a60a85a36abd3e748ea9da52cf)
- eliminate Coverity defects [`f730f49`](https://github.com/ImageMagick/ImageMagick6/commit/f730f493939fbe42ae80a0b58d2777d56427e8db)
- eliminate leak in Freetype streaming interface [`980bfe2`](https://github.com/ImageMagick/ImageMagick6/commit/980bfe2047986aab0400d517827ab1761ea82733)
- prevent double free in Freetype streaming interface [`212564a`](https://github.com/ImageMagick/ImageMagick6/commit/212564a2693c2e9189d12e11a1d67907ad2cf970)
- eliminate Coverity defects [`6ef3cb2`](https://github.com/ImageMagick/ImageMagick6/commit/6ef3cb2a758a3dd806df968e89a9fd7c51fed4bd)
- fix fill-opacity special case where the fill color alpha is fully transparent [`83bd597`](https://github.com/ImageMagick/ImageMagick6/commit/83bd597344deb87274a774452145654507335690)
- eliminate coverity defects [`68fe465`](https://github.com/ImageMagick/ImageMagick6/commit/68fe465b16694f67f1e09e8c1c7fbaec396e4a41)
- release [`e2d55af`](https://github.com/ImageMagick/ImageMagick6/commit/e2d55af5bad16596e3bb43c10eb47b5bfec435c9)

## [6.9.12-44](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-43...6.9.12-44) - 2022-03-27

### Commits

- ... [`2095de7`](https://github.com/ImageMagick/ImageMagick6/commit/2095de7a1ffeb72fbb8b3dd72e70c2c23c534991)
- https://github.com/ImageMagick/ImageMagick/issues/4974 [`1f860f5`](https://github.com/ImageMagick/ImageMagick6/commit/1f860f52bd8d58737ad883072203391096b30b51)
- https://github.com/ImageMagick/ImageMagick/issues/4975 [`5eb276a`](https://github.com/ImageMagick/ImageMagick6/commit/5eb276ac65c0fbc55546ecbf5f92942f39d7d2ff)
- lastest changes [`70202da`](https://github.com/ImageMagick/ImageMagick6/commit/70202daef0dffb77a48100185724f8eac13d82c4)
- enforce one `id` per MIFF image [`ab0133d`](https://github.com/ImageMagick/ImageMagick6/commit/ab0133d9e5eefbaa8eb8050e1600be63b8734db9)
- latest changes [`34cbd5f`](https://github.com/ImageMagick/ImageMagick6/commit/34cbd5f1249944f8e96b718a9e9632b9b5ac2b2f)
- https://github.com/ImageMagick/ImageMagick/pull/4986 [`29c8abc`](https://github.com/ImageMagick/ImageMagick6/commit/29c8abce0da56b536542f76a9ddfebdaab5b2943)
- reset id [`ee32452`](https://github.com/ImageMagick/ImageMagick6/commit/ee32452ea6b54e3566a82aa60bf2a17de29b48d5)
- reset id [`e87f9fd`](https://github.com/ImageMagick/ImageMagick6/commit/e87f9fdb519be34daeed85f9d9bd98740518d53b)
- over allocate quantum pixel buffer [`db2fd39`](https://github.com/ImageMagick/ImageMagick6/commit/db2fd39c1ba4fc9da61cc874506e28f5822bd82a)
- https://github.com/ImageMagick/ImageMagick/issues/4987 [`7962da1`](https://github.com/ImageMagick/ImageMagick6/commit/7962da1bc92349f205fce473f07ab6c1dffa29e6)
- no suitable delegate utility for CGM or FIG formats [`19b1aa9`](https://github.com/ImageMagick/ImageMagick6/commit/19b1aa98f5e4ba72bf238bceb99fe2855f6dbd16)
- https://github.com/ImageMagick/ImageMagick/issues/4988 [`e6ea587`](https://github.com/ImageMagick/ImageMagick6/commit/e6ea5876e0228165ee3abc6e959aa174cee06680)
- cosmetic [`8192e98`](https://github.com/ImageMagick/ImageMagick6/commit/8192e981094a776529fd37eb1744bc265f73b89b)
- cosmetic [`dfb7339`](https://github.com/ImageMagick/ImageMagick6/commit/dfb73390fdae16eb53000574e2fdcc65e4883061)
- speculative allocation since we don't yet know the quantum type [`cf8f393`](https://github.com/ImageMagick/ImageMagick6/commit/cf8f3935cfcc97a4827fe7f60bb5b1b0de6f7eec)
- pending release [`64ad194`](https://github.com/ImageMagick/ImageMagick6/commit/64ad1943ce394c78a6884bf2064e8d03b5238e05)
- revert [`9d10d1e`](https://github.com/ImageMagick/ImageMagick6/commit/9d10d1e402c71972fbcde2fd3380c94f3ee2989b)
- set quantum extent [`9e2fbee`](https://github.com/ImageMagick/ImageMagick6/commit/9e2fbee19683fca2aca3425fdc45dab8dc4a0054)
- revert [`1811528`](https://github.com/ImageMagick/ImageMagick6/commit/1811528ecccb81cc744a9ec49e1b292edac56aa5)
- pending release [`44a7f86`](https://github.com/ImageMagick/ImageMagick6/commit/44a7f8628ef12e1acf1340cad31c8cd3ffc05d8f)
- release [`b350dd1`](https://github.com/ImageMagick/ImageMagick6/commit/b350dd13b3c748973249f9cb63e431f1e488f2fc)

## [6.9.12-43](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-42...6.9.12-43) - 2022-03-20

### Commits

- ... [`96d197f`](https://github.com/ImageMagick/ImageMagick6/commit/96d197f14932d4ba8a116e06fe306403ea1e32f1)
- https://github.com/ImageMagick/ImageMagick/issues/4927 [`594366f`](https://github.com/ImageMagick/ImageMagick6/commit/594366fd3a5268d0456c4f60c5746a9f586ab035)
- https://github.com/ImageMagick/ImageMagick/issues/4927 [`932cf02`](https://github.com/ImageMagick/ImageMagick6/commit/932cf023db383394c4ec304c95730aed631c57d2)
- no need to check for &lt; 0 [`dead6a8`](https://github.com/ImageMagick/ImageMagick6/commit/dead6a806786eb2712dd76c38e3ff75c2f94997b)
- Changed the format of MAGICK_GIT_REVISION and use this in -version. [`bd49573`](https://github.com/ImageMagick/ImageMagick6/commit/bd495730646575af3c867ed09adc8588061079ab)
- correct date format [`625ff11`](https://github.com/ImageMagick/ImageMagick6/commit/625ff113cc9acf864c56c266471829bb19439299)
- Coders: https://github.com/ImageMagick/ImageMagick/issues/4947 [`78f03b6`](https://github.com/ImageMagick/ImageMagick6/commit/78f03b619d08d7c2e0fcaccab407e3ac93c2ee8f)
- Coders: proper check for out of bounds per https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=45640 [`5468786`](https://github.com/ImageMagick/ImageMagick6/commit/5468786406b323fef6a5fe50bc56dabde3da4130)
- Coders: https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=42549 [`de6ada9`](https://github.com/ImageMagick/ImageMagick6/commit/de6ada9a068b01494bfb848024ed46942da9d238)
- Coders: eliminate compiler warnings [`ee332c5`](https://github.com/ImageMagick/ImageMagick6/commit/ee332c511445a1fb2934f40246c3c958aefd73e9)
- Pull request: https://github.com/ImageMagick/ImageMagick/pull/4963 [`450949e`](https://github.com/ImageMagick/ImageMagick6/commit/450949ed017f009b399c937cf362f0058eacc5fa)
- Coders: PS and EPS %%BoundingBox not being parsed #4961 [`2a67214`](https://github.com/ImageMagick/ImageMagick6/commit/2a67214abc2410931064b1f4e2c01f177d768edf)
- magick: support getentropy() [`d29a057`](https://github.com/ImageMagick/ImageMagick6/commit/d29a057a3689f7b944b879dee92e7d39a33bf3cc)
- build: release [`2d5e8e3`](https://github.com/ImageMagick/ImageMagick6/commit/2d5e8e387e1c6daaf45f8efd1c24ee6a53e70e01)
- getentropy() requires sys/random.h include [`005bac2`](https://github.com/ImageMagick/ImageMagick6/commit/005bac2904c18bc6f03a2ac31bdda51005411355)
- build: pending release [`775c781`](https://github.com/ImageMagick/ImageMagick6/commit/775c7817f3700514173e0655776e0d9465e93d6c)

## [6.9.12-42](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-41...6.9.12-42) - 2022-03-04

### Commits

- ... [`8f1f6c3`](https://github.com/ImageMagick/ImageMagick6/commit/8f1f6c32bfb13ac1e8b8a7ce2f59a28ef06cb18b)
- https://github.com/ImageMagick/ImageMagick/issues/4870 [`8b7b17c`](https://github.com/ImageMagick/ImageMagick6/commit/8b7b17c8fef72dab479e6ca676676d8c5e395dd6)
- https://github.com/ImageMagick/ImageMagick/issues/4876 [`52e5cc1`](https://github.com/ImageMagick/ImageMagick6/commit/52e5cc1988b15b9a6f3d7e9e3b7b72e3a346cfc9)
- ... [`4c2da37`](https://github.com/ImageMagick/ImageMagick6/commit/4c2da37f2bcc98059f44cecf304e8b3c53664bfd)
- canonical copyright notice [`1e5a283`](https://github.com/ImageMagick/ImageMagick6/commit/1e5a28310d73e9c8c29fad113c872351340595a3)
- https://github.com/ImageMagick/ImageMagick/issues/966 [`2db42a9`](https://github.com/ImageMagick/ImageMagick6/commit/2db42a9e1dde7e88dc370deb04a3be48c01dedf5)
- escape \n character [`32a4bf3`](https://github.com/ImageMagick/ImageMagick6/commit/32a4bf395e8201896c0a21f95661766bed41e470)
- https://github.com/ImageMagick/ImageMagick/issues/966 [`d9544e7`](https://github.com/ImageMagick/ImageMagick6/commit/d9544e78bfe55361b7768ddb00eb24b7f33f2137)
- https://github.com/ImageMagick/ImageMagick/issues/4888 [`ba2242d`](https://github.com/ImageMagick/ImageMagick6/commit/ba2242da46bfbd2cc4890486ff147a0113e08735)
- https://github.com/ImageMagick/ImageMagick/issues/4888 [`2eb8b86`](https://github.com/ImageMagick/ImageMagick6/commit/2eb8b8660dac0d647a7045a6af7f3e8fcca1d8f8)
- https://github.com/ImageMagick/ImageMagick/issues/966 [`bb79523`](https://github.com/ImageMagick/ImageMagick6/commit/bb795235696e2ace0f3d0b5703065a4b9a882f04)
- throw exception on reserved filename character (\xff) [`8215fc2`](https://github.com/ImageMagick/ImageMagick6/commit/8215fc2e71513877d3040fbddfd1f16ca54499a7)
- auto-generate the change log from git commit [`553ca1b`](https://github.com/ImageMagick/ImageMagick6/commit/553ca1b6e5bcc7d89af226cecfa6b6197a90a98c)
- Changed trigger for release. [`552bddd`](https://github.com/ImageMagick/ImageMagick6/commit/552bddd79749d8195cf5a1871929076adf9a479e)
- ChangeLog =&gt; ChangeLog.md [`8a6726a`](https://github.com/ImageMagick/ImageMagick6/commit/8a6726af81ac40b41e962cafa8fd014d2659d432)
- Fixed memory leak in ThumbnailImage. [`161f49b`](https://github.com/ImageMagick/ImageMagick6/commit/161f49b3b6a7d3121a566654f12916700d7f2d07)
- pending release [`4f420a4`](https://github.com/ImageMagick/ImageMagick6/commit/4f420a43ce112948baa8de9a1ba56ee7b17afb0f)
- pending release [`dad876f`](https://github.com/ImageMagick/ImageMagick6/commit/dad876ff6b5e873bc59e0661d40e157eb599fcc1)

## [6.9.12-41](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-40...6.9.12-41) - 2022-02-21

### Commits

- ... [`ba6e51f`](https://github.com/ImageMagick/ImageMagick6/commit/ba6e51f8e3b49c3d5015df5c4d152e07a37007aa)
- https://github.com/ImageMagick/ImageMagick/issues/4761 [`77d68d3`](https://github.com/ImageMagick/ImageMagick6/commit/77d68d3e554ecd0e38ceb6a3f1decf65a69362c5)
- https://github.com/ImageMagick/ImageMagick/discussions/4755 [`1e86532`](https://github.com/ImageMagick/ImageMagick6/commit/1e8653229aeea1a6731ca3632bf5963b417312ed)
- https://github.com/ImageMagick/ImageMagick/issues/4843 [`b24793c`](https://github.com/ImageMagick/ImageMagick6/commit/b24793c396083176cbf019a09847ad3ab427e240)
- ... [`cecdf6f`](https://github.com/ImageMagick/ImageMagick6/commit/cecdf6f89642589221edc543144d45c5bde71b77)
- Removed the xtrn coder. [`768f648`](https://github.com/ImageMagick/ImageMagick6/commit/768f648cce36a641b54092d78117435996c74a9a)
- Removed the xtrn coder. [`854e7be`](https://github.com/ImageMagick/ImageMagick6/commit/854e7be5f0ce94c0a431d49a1c82a9eb50916be4)
- ... [`695af8d`](https://github.com/ImageMagick/ImageMagick6/commit/695af8d4be0d25b36129d7b3fdf5a1b991216784)
- fix compiler exception under Cygwin [`32315c9`](https://github.com/ImageMagick/ImageMagick6/commit/32315c92a4e31c0b75fb88548c0bf40242f0e5f1)
- ... [`45d3733`](https://github.com/ImageMagick/ImageMagick6/commit/45d37331ef1a38712740e9bd7090fb855557b7cb)
- remove reference to ImageMagickObject [`d64a152`](https://github.com/ImageMagick/ImageMagick6/commit/d64a15289a17a9d1d9856758f2ba82b75325f370)
- remove references to ImageMagickObject [`1e63c5c`](https://github.com/ImageMagick/ImageMagick6/commit/1e63c5c2d7f2c1d5c6aba0e8935ee855656cbb46)
- ... [`757c88c`](https://github.com/ImageMagick/ImageMagick6/commit/757c88cfe941df0cff8f2fef4681bd2b665c091c)
- pending release [`fd143dc`](https://github.com/ImageMagick/ImageMagick6/commit/fd143dc849b6c191464f40e581b0abe344b6e41e)
- Raise exception when image could not be read but no exception was raised. [`3e15c68`](https://github.com/ImageMagick/ImageMagick6/commit/3e15c68efcb1e6383c93e7dfe38ba6c37e614d1b)
- Whitespace. [`b36de79`](https://github.com/ImageMagick/ImageMagick6/commit/b36de79c6cb913f4423f7eb71901d9f07946f573)
- Removed NTGhostscriptDLL and NTGhostscriptLoadDLL from the private header. [`70b7dfa`](https://github.com/ImageMagick/ImageMagick6/commit/70b7dfaf4d2f75af8b649d542d49374d6f447c11)
- Fixes for installation in a folder that contains non ASCII characters. [`e3d32a2`](https://github.com/ImageMagick/ImageMagick6/commit/e3d32a2bdb9e50ddb2fd5966c847f0726e128815)
- off-by-one fix [`d0a2bc4`](https://github.com/ImageMagick/ImageMagick6/commit/d0a2bc44117217a7619d6ade90af0f40d9321c6e)
- don't over-allocate thread-specific data [`b61069a`](https://github.com/ImageMagick/ImageMagick6/commit/b61069a33bab43a022992b3f7c81a50e06a7b45a)
- pending release [`8a8673a`](https://github.com/ImageMagick/ImageMagick6/commit/8a8673a9bc1a7b915252645f305a65f0c990b491)
- no need for conditional compile [`d5fe059`](https://github.com/ImageMagick/ImageMagick6/commit/d5fe0590573b15208f302d57e0b1c97a60e3d16d)
- rename method to TLS-moniker, thread local storage [`8860c28`](https://github.com/ImageMagick/ImageMagick6/commit/8860c28c64ae2cf5717e309325592c1ccb7cb969)
- cosmetic [`6831beb`](https://github.com/ImageMagick/ImageMagick6/commit/6831bebd3067bddc10e954fe09bc98a3e6947be7)
- cosmetic [`c02d827`](https://github.com/ImageMagick/ImageMagick6/commit/c02d827078d59950e19e169ffeb3d988d0e1185c)
- pending release [`9ce4eba`](https://github.com/ImageMagick/ImageMagick6/commit/9ce4ebad1337a10bc9d6b74bddd57ad7dc3cde70)
- pending release [`b855d8e`](https://github.com/ImageMagick/ImageMagick6/commit/b855d8ec0bb360deb7d80a14b5c1a5a1ffc47ee1)
- https://github.com/ImageMagick/ImageMagick/issues/4865 [`e6d7f78`](https://github.com/ImageMagick/ImageMagick6/commit/e6d7f782fc1b6484c52fe7fb987c06559b489726)
- pending release [`e7418d5`](https://github.com/ImageMagick/ImageMagick6/commit/e7418d54c54b4646505ba95ce6458f352a94debf)
- https://github.com/ImageMagick/ImageMagick/issues/4867 [`8c1bf89`](https://github.com/ImageMagick/ImageMagick6/commit/8c1bf8917a7a23daa6aaa03bb4293fd9ff7859a2)
- pending release [`9b99699`](https://github.com/ImageMagick/ImageMagick6/commit/9b9969944c92ccaf4fa7d34c1c258a794a1e23b9)

## [6.9.12-40](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-39...6.9.12-40) - 2022-02-15

### Commits

- ... [`4fd78b8`](https://github.com/ImageMagick/ImageMagick6/commit/4fd78b838c09c88ff3acf43a0799a002d2f873cf)
- https://github.com/ImageMagick/ImageMagick/issues/4822 [`5a76293`](https://github.com/ImageMagick/ImageMagick6/commit/5a7629343bb280a1a177818e6e40776c7484d649)
- one off when debugging [`cb6374d`](https://github.com/ImageMagick/ImageMagick6/commit/cb6374d6fe7fec6651b1d1dd4ee7ec97c662c610)
- display last debugging character [`e6a76f8`](https://github.com/ImageMagick/ImageMagick6/commit/e6a76f8bfb9a8edfbd4cdc44e79eb080f164cf71)
- alpha is never zero [`ff04a51`](https://github.com/ImageMagick/ImageMagick6/commit/ff04a51f4f89813c319f157c0aa993f36b944815)
- https://github.com/ImageMagick/ImageMagick/issues/4837 [`00e5d3a`](https://github.com/ImageMagick/ImageMagick6/commit/00e5d3a9a033182fcf704e4b1eae9e569fb85244)
- https://github.com/ImageMagick/ImageMagick/issues/4837 [`a339e1f`](https://github.com/ImageMagick/ImageMagick6/commit/a339e1f47dd09d1765e971f7e104d34a2e50785c)
- revert [`dc25885`](https://github.com/ImageMagick/ImageMagick6/commit/dc25885dfb4d516d6ef58ba77bfc47e8799acfed)
- cosmetic [`1da04da`](https://github.com/ImageMagick/ImageMagick6/commit/1da04dabe110e22954b33927567544b33e97b7a7)
- off-by-one fix [`e41e298`](https://github.com/ImageMagick/ImageMagick6/commit/e41e29898936ca76b0def5126771733e0954191e)
- fix unitialized value [`ce4d5cb`](https://github.com/ImageMagick/ImageMagick6/commit/ce4d5cb663cb3d701d63515edbeee561b71eae39)
- https://github.com/ImageMagick/ImageMagick/issues/4841 [`f5aeb09`](https://github.com/ImageMagick/ImageMagick6/commit/f5aeb0989d9889d85b2d66a106a670386872a8c6)
- off-by-one fix [`409d6db`](https://github.com/ImageMagick/ImageMagick6/commit/409d6db86bae76c8f7401dc1c09c4349b8ca8352)
- pending release [`3264d72`](https://github.com/ImageMagick/ImageMagick6/commit/3264d72944d6f2df8f80ecb3d837da1431db37a6)

## [6.9.12-39](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-38...6.9.12-39) - 2022-02-12

### Commits

- ... [`e5ab86b`](https://github.com/ImageMagick/ImageMagick6/commit/e5ab86b9f52a8452fb00099f29a51763a5b114ff)
- possible performance optimization [`1e04814`](https://github.com/ImageMagick/ImageMagick6/commit/1e04814e2e28c9a22f082b5c87cc5cf20642ad0d)
- ... [`bcf9658`](https://github.com/ImageMagick/ImageMagick6/commit/bcf9658a637a7c6993c7203382235fd3fabb7015)
- ... [`fb8b7d6`](https://github.com/ImageMagick/ImageMagick6/commit/fb8b7d60e6469c38b9c16436a7a472d57d9b8562)
- Fixed build error. [`8cb3ec3`](https://github.com/ImageMagick/ImageMagick6/commit/8cb3ec3f676b7b566f0590536894f11fac6cf8b4)
- optimize reading of XPM properties [`cd103b8`](https://github.com/ImageMagick/ImageMagick6/commit/cd103b81ca7814533192f340053b388c6825ec83)
- https://github.com/ImageMagick/ImageMagick/discussions/4813 [`666ab9a`](https://github.com/ImageMagick/ImageMagick6/commit/666ab9ad9552fac12f92d2cf53173bea3d848255)
- Removed methods that have been renamed. [`88f63de`](https://github.com/ImageMagick/ImageMagick6/commit/88f63de88c6242bfdbb669b90f44c1827f71aebf)
- Removed IsAVI check. [`6eb9f96`](https://github.com/ImageMagick/ImageMagick6/commit/6eb9f96e781996b71ead9d25182be0e84bfdb89f)
- cosmetic [`5683607`](https://github.com/ImageMagick/ImageMagick6/commit/56836073a8cc42127b265280dfb0d5dcb4bc915b)
- https://github.com/ImageMagick/ImageMagick/issues/4822 [`0977428`](https://github.com/ImageMagick/ImageMagick6/commit/097742836e252be7aba65c00877722f5eae8e851)
- ... [`e29fbed`](https://github.com/ImageMagick/ImageMagick6/commit/e29fbed480a847fd70671ffb445769cc07f87b40)
- https://github.com/ImageMagick/ImageMagick/issues/4828 [`37ac2f0`](https://github.com/ImageMagick/ImageMagick6/commit/37ac2f0185a2afc88de705937f1e1e57004aa6ba)
- prevent integer overflow [`a69648d`](https://github.com/ImageMagick/ImageMagick6/commit/a69648d9d3eb9855eeb6089a692c689581d85cff)
- Corrected UTF-16 big endian encoding. [`71e590e`](https://github.com/ImageMagick/ImageMagick6/commit/71e590ed3885ef5e2d48918809d8a3a8cfefccba)
- https://github.com/ImageMagick/ImageMagick/issues/4830 [`409d422`](https://github.com/ImageMagick/ImageMagick6/commit/409d42205927c98cbb852ca96e109716f38f04ab)
- update copyright year [`f5cb4ce`](https://github.com/ImageMagick/ImageMagick6/commit/f5cb4ce9319066b5b4740f725d9f0f8a52368be8)
- correct copyright year [`99ef124`](https://github.com/ImageMagick/ImageMagick6/commit/99ef124d080560a9df5a0c177a82c3ccc2ca6ca9)
- pending release [`002c3d7`](https://github.com/ImageMagick/ImageMagick6/commit/002c3d7c493de002eaa605ade574830e7e8d1693)

## [6.9.12-38](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-37...6.9.12-38) - 2022-02-05

### Commits

- check if image extent is NaN [`0608714`](https://github.com/ImageMagick/ImageMagick6/commit/0608714e4b8df32180359ba502990693ccfe3115)
- ... [`0ec8137`](https://github.com/ImageMagick/ImageMagick6/commit/0ec813759359a1a9f4e37a1696bb2f967c917776)
- VID images not permitted when compositing [`f4529c0`](https://github.com/ImageMagick/ImageMagick6/commit/f4529c0dcf3a8f96c438086b28fbef8338cda0b1)
- avoid deep recursion [`513854d`](https://github.com/ImageMagick/ImageMagick6/commit/513854d34c8e505207c4c4a4cb0932ef7770fa05)
- ... [`c726d86`](https://github.com/ImageMagick/ImageMagick6/commit/c726d861a67aadf697eb35b8847f6431b47dec1e)
- https://github.com/ImageMagick/ImageMagick/issues/4793 [`dd65574`](https://github.com/ImageMagick/ImageMagick6/commit/dd655741bb71f7a129757fc0676e8aa328b44dad)
- Corrected setting delay. [`bd7f6d7`](https://github.com/ImageMagick/ImageMagick6/commit/bd7f6d781953b415e7d5f4830feebbe87a54e62f)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=44401 [`e94e616`](https://github.com/ImageMagick/ImageMagick6/commit/e94e616aff39358e09d6ae3180baf3cb59923690)
- https://github.com/ImageMagick/ImageMagick/issues/4807 [`bcbcfeb`](https://github.com/ImageMagick/ImageMagick6/commit/bcbcfeb3b697e8ec1a105dc7c7099f5f9191f172)
- reference https://github.com/ImageMagick/ImageMagick/issues/4807 [`f2ee9a7`](https://github.com/ImageMagick/ImageMagick6/commit/f2ee9a74d52794b4ef9e62e71d4906d5cab9ef27)
- pending release [`fa0b758`](https://github.com/ImageMagick/ImageMagick6/commit/fa0b758566ef994436fc9d9c14b68b433e2dd513)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=44424 [`bbf05a3`](https://github.com/ImageMagick/ImageMagick6/commit/bbf05a3449db3555cc05f4f3cacf172d6a0d35cc)
- release [`b5bb28a`](https://github.com/ImageMagick/ImageMagick6/commit/b5bb28a0ca2e53b668e4057a0cb04166ef781793)

## [6.9.12-37](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-36...6.9.12-37) - 2022-01-29

### Commits

- bump patch level version [`e662b69`](https://github.com/ImageMagick/ImageMagick6/commit/e662b69dd2cb3209339aff3c277493ef18f72a92)
- check for excessive color name length [`1025a9b`](https://github.com/ImageMagick/ImageMagick6/commit/1025a9b0373dd194fc4529424e80396f35b1bbf4)
- restore MPRI URI [`d624f7f`](https://github.com/ImageMagick/ImageMagick6/commit/d624f7f008450eded4f006517e3275647eb69864)
- pending release [`f0b31c1`](https://github.com/ImageMagick/ImageMagick6/commit/f0b31c169c00ad9e688b89e6a17e2678cc91c733)
- permit compositing MPRI images [`4dd4d0d`](https://github.com/ImageMagick/ImageMagick6/commit/4dd4d0df449acb13fb859041b4996af58243e352)
- pending release [`f1e0995`](https://github.com/ImageMagick/ImageMagick6/commit/f1e09958774501f6e39e4b06deed0c351b8158ca)

## [6.9.12-36](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-35...6.9.12-36) - 2022-01-28

### Commits

- It's a new dawn; It's a new day; It's a new life; For ImageMagick [`49ea804`](https://github.com/ImageMagick/ImageMagick6/commit/49ea804be9295c12b457843271042e2e3521750e)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=43967 [`f5f594a`](https://github.com/ImageMagick/ImageMagick6/commit/f5f594abe588bcc6ee870998bc801ede67e5b8b5)
- Added missing version check. [`9cfea23`](https://github.com/ImageMagick/ImageMagick6/commit/9cfea235600550f02b2df61c276c438ab031441e)
- ... [`1ac7d3d`](https://github.com/ImageMagick/ImageMagick6/commit/1ac7d3da9c45ee15ef7421d3ae62943f72f3cdab)
- check for excessive memory request when drawing [`50aeffe`](https://github.com/ImageMagick/ImageMagick6/commit/50aeffee5b880716bc3fbca6edf990a853b04a4d)
- https://github.com/ImageMagick/ImageMagick/issues/4766 [`77fc0b9`](https://github.com/ImageMagick/ImageMagick6/commit/77fc0b952bf505ff10b5abb94b33206f31056e06)
- promote blocksize from int to ssize_t [`ba2e0ef`](https://github.com/ImageMagick/ImageMagick6/commit/ba2e0efa42a0ac656fa4b01beb6500915ee11bcd)
- pending release [`fca98f0`](https://github.com/ImageMagick/ImageMagick6/commit/fca98f0ad524641afd5f0c4bf42852ebaf8c1c27)
- https://github.com/ImageMagick/ImageMagick/issues/4771 [`8e326c6`](https://github.com/ImageMagick/ImageMagick6/commit/8e326c63f27c544e1dbbb1a329256306e93f1a70)
- pending release [`fee44f7`](https://github.com/ImageMagick/ImageMagick6/commit/fee44f7b445cdca56a5ec19a2878608a511098c9)
- PDF unicode title [`bf36be4`](https://github.com/ImageMagick/ImageMagick6/commit/bf36be46887cdc65c8add8c6bfed20a0c4ae290d)
- pending release [`44065d3`](https://github.com/ImageMagick/ImageMagick6/commit/44065d3e7ede7012ab32bb560d838eed9507720d)

## [6.9.12-35](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-34...6.9.12-35) - 2022-01-22

### Commits

- ... [`e8b78e7`](https://github.com/ImageMagick/ImageMagick6/commit/e8b78e7bae67150667f3037932d0b3f1bc00434d)
- improved fix for possible DoS for certain SVG constructs [`84ec305`](https://github.com/ImageMagick/ImageMagick6/commit/84ec30550c3146f525383f18a786a6bbd5028a93)
- cosmetic [`623e681`](https://github.com/ImageMagick/ImageMagick6/commit/623e6813fcfe68729d78cc27b4d9bc77a678c760)
- Removed comment. [`f5bac9b`](https://github.com/ImageMagick/ImageMagick6/commit/f5bac9b20849fc7c540550e15f3ae839faf506fb)
- Fixed Windows build. [`e838900`](https://github.com/ImageMagick/ImageMagick6/commit/e838900d9380feba6900adc7537eea852cd478d5)
- Added checks for invalid PSD channel size. [`e26d718`](https://github.com/ImageMagick/ImageMagick6/commit/e26d718edaf73793c7a0f2f609ecf662fcccd562)
- permit 4GB blocks [`23b4299`](https://github.com/ImageMagick/ImageMagick6/commit/23b42998f5b3345d1915d4222cc2e858badca639)
- https://github.com/ImageMagick/ImageMagick/issues/4629 [`dea9fb3`](https://github.com/ImageMagick/ImageMagick6/commit/dea9fb319c9f4564662e0f1705856854aec01605)
- https://github.com/ImageMagick/ImageMagick/issues/4639 [`2318bfb`](https://github.com/ImageMagick/ImageMagick6/commit/2318bfb4009f8742b4c09007f3c8ba72bac7bf89)
- Fixed possible memory leak. [`e5bee23`](https://github.com/ImageMagick/ImageMagick6/commit/e5bee2335ec13cff0171e9517f862298bb7f0c0a)
- https://github.com/ImageMagick/ImageMagick/issues/4654 [`aee3f00`](https://github.com/ImageMagick/ImageMagick6/commit/aee3f004aa62bafb20dcb7c7c0675ee7d5bf9255)
- Use same checks as in IM7. [`a93c000`](https://github.com/ImageMagick/ImageMagick6/commit/a93c000f4585e9ef3b0a8a8f55bdcc25575e21b7)
- Build ImageMagick on Windows with VisualStudio 2022 instead. [`a9b405b`](https://github.com/ImageMagick/ImageMagick6/commit/a9b405b9e1bd219351d8961c9ccfddbc2a299d3a)
- Allow workflow dispatch. [`809c4ce`](https://github.com/ImageMagick/ImageMagick6/commit/809c4cefefea926887e17f63093a98223c62d857)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=43390 [`2ff94fa`](https://github.com/ImageMagick/ImageMagick6/commit/2ff94fab76c89707ed241d3a85e3881d88d1b032)
- Changed the build of configure to 64-bit. [`f5cb4bb`](https://github.com/ImageMagick/ImageMagick6/commit/f5cb4bb894806c595b08591f7ff755caed117fe6)
- https://github.com/ImageMagick/ImageMagick/issues/4679 [`8854349`](https://github.com/ImageMagick/ImageMagick6/commit/88543494464bf94ef3430ba33bb34c62ba5050d6)
- https://github.com/ImageMagick/ImageMagick/issues/4681 [`21bddc2`](https://github.com/ImageMagick/ImageMagick6/commit/21bddc28dcc31dde7d23b25009e1efbedcbae174)
- eliminate rare memory leak [`cf21bd4`](https://github.com/ImageMagick/ImageMagick6/commit/cf21bd4a4dd173a156c529082b6eb074c6aced71)
- revert [`dada640`](https://github.com/ImageMagick/ImageMagick6/commit/dada640f2732a4ae8e524ac95c1b998cf0102a80)
- ... [`a4d1e39`](https://github.com/ImageMagick/ImageMagick6/commit/a4d1e399130e50698cb1210e95224f7cd301ba8d)
- revert [`46859fd`](https://github.com/ImageMagick/ImageMagick6/commit/46859fda719f814ec7e1fbbc37ed66b6706d4094)
- ... [`bbb86a2`](https://github.com/ImageMagick/ImageMagick6/commit/bbb86a2c59fabc73d0262c70ae71ce80a89b4c5e)
- https://github.com/ImageMagick/ImageMagick/issues/4704 [`25c9e4d`](https://github.com/ImageMagick/ImageMagick6/commit/25c9e4df716f34519d346369892b030ee5155312)
- ... [`f7a43f3`](https://github.com/ImageMagick/ImageMagick6/commit/f7a43f3552a6f47a1258a524ec8ed33250601839)
- https://github.com/ImageMagick/ImageMagick/issues/4660 [`fd1df0b`](https://github.com/ImageMagick/ImageMagick6/commit/fd1df0b69806c4d820c277759b5171795502dd70)
- https://github.com/ImageMagick/ImageMagick/issues/4704 [`9002280`](https://github.com/ImageMagick/ImageMagick6/commit/90022807243230deea06b9dcc874d2a41c611631)
- eliminate C++ compiler warnings [`08dd651`](https://github.com/ImageMagick/ImageMagick6/commit/08dd6515f47bf4276797b46b9c81e016c7c46993)
- fuzzy equality check [`0256b55`](https://github.com/ImageMagick/ImageMagick6/commit/0256b550e7fd2bcec82802f4c349f6e64ad1d06a)
- zero papersize geometry [`4382359`](https://github.com/ImageMagick/ImageMagick6/commit/4382359ee5d87266c25646f68da20d4229d771bd)
- AVIF is supported by the HEIC coder [`2287dca`](https://github.com/ImageMagick/ImageMagick6/commit/2287dca493099e423ca751bf55a3f114fc848a96)
- pending release [`aff974e`](https://github.com/ImageMagick/ImageMagick6/commit/aff974eb0da8eaee7edf3acbe945a2d8bb4a4c8e)
- Added move to use the installed version of Strawberry Perl instead. [`d68e6fa`](https://github.com/ImageMagick/ImageMagick6/commit/d68e6faf1d817c9b4db97b1643226dfce2a90dfc)
- pending release [`d02bc00`](https://github.com/ImageMagick/ImageMagick6/commit/d02bc0072070ef2f33ee6d8acca436a720b9861b)

## [6.9.12-34](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-33...6.9.12-34) - 2021-12-22

### Commits

- ... [`39b8934`](https://github.com/ImageMagick/ImageMagick6/commit/39b8934f42179a4a79b41d3fa141b8fac7064ea2)
- ... [`8093989`](https://github.com/ImageMagick/ImageMagick6/commit/8093989a6bf0ea36a2e81d61400e47c9cdba3032)
- Set the colorspace after the width and height of the image have been checked. [`3fd8496`](https://github.com/ImageMagick/ImageMagick6/commit/3fd8496d027b4b03e622cbf093e0b28d1e30d4ac)
- Corrected method call. [`05259b5`](https://github.com/ImageMagick/ImageMagick6/commit/05259b51165aa26f9ec265e201315391a5a958b4)
- check for unbalanced parenthesis [`6fdd03b`](https://github.com/ImageMagick/ImageMagick6/commit/6fdd03b7fef68cfdb1c0f87d5e0e72a29f2d0336)
- https://github.com/ImageMagick/ImageMagick/issues/4626 [`c10351c`](https://github.com/ImageMagick/ImageMagick6/commit/c10351c16b8d2cabd11d2627a02de522570f6ceb)
- pending release [`0b0cbf7`](https://github.com/ImageMagick/ImageMagick6/commit/0b0cbf7b0f5c2ddcd41c85fc2da64d4771f80018)

## [6.9.12-33](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-32...6.9.12-33) - 2021-12-18

### Commits

- ... [`3deb899`](https://github.com/ImageMagick/ImageMagick6/commit/3deb89958f6787deca910570ff5fb8d27210b554)
- https://github.com/ImageMagick/ImageMagick/security/code-scanning/31 [`094e143`](https://github.com/ImageMagick/ImageMagick6/commit/094e143714873a2903093ea6c128af267ef8c997)
- revert [`7cbce51`](https://github.com/ImageMagick/ImageMagick6/commit/7cbce514e6a0f530b5f50b960f6d95c62c9416f5)
- Improved adjustment of page offset when resizing an image. [`accf336`](https://github.com/ImageMagick/ImageMagick6/commit/accf33670091ef833b45ef5bb913812e16469333)
- Corrected the built-in video encoder and decoder. [`91320cc`](https://github.com/ImageMagick/ImageMagick6/commit/91320cc53f6c5e8b59b5e22e0042d62b230344ba)
- improved adjustment of page offset when resizing an image [`c8bb427`](https://github.com/ImageMagick/ImageMagick6/commit/c8bb4278eb7be195cc45ba08e617987cf34dad1e)
- https://github.com/ImageMagick/ImageMagick/issues/4558 [`fb428af`](https://github.com/ImageMagick/ImageMagick6/commit/fb428af466701e487cfd0f657c78e1f74da4c12b)
- Corrected method name. [`15aadb7`](https://github.com/ImageMagick/ImageMagick6/commit/15aadb7691a3a8cd47cbbae9ca3ec58c01acc3c3)
- Swapped the Sync8BimProfile and the SyncExifProfile methods. [`77b718c`](https://github.com/ImageMagick/ImageMagick6/commit/77b718c3f5d5e39710d227f2bb6a7fb65abd4c57)
- Corrected typecast. [`87ce0d8`](https://github.com/ImageMagick/ImageMagick6/commit/87ce0d8fa8446b142938f1be63cf3e6b866697cf)
- Also sync the exif profile inside the 8bim profile. [`3be80bc`](https://github.com/ImageMagick/ImageMagick6/commit/3be80bc9c9b5e49a6266b680e38d39d5ecaeaadb)
- Restored debug message. [`2ab41fb`](https://github.com/ImageMagick/ImageMagick6/commit/2ab41fbf336faf0fbb9d3217b72c6f6336b7767b)
- https://github.com/ImageMagick/ImageMagick/issues/4587 [`526a3d1`](https://github.com/ImageMagick/ImageMagick6/commit/526a3d19790b753e4d7f63515dc667a3472f9eda)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=42504 [`9f7310b`](https://github.com/ImageMagick/ImageMagick6/commit/9f7310b7a3c80f132c548ffb8f29eea7dabae8c2)
- ... [`add9cb1`](https://github.com/ImageMagick/ImageMagick6/commit/add9cb14e14eef02806715d97abcf5d04a3e55dd)
- pending release [`a518f31`](https://github.com/ImageMagick/ImageMagick6/commit/a518f310bc77991712a53f6984f9f0edce706174)

## [6.9.12-32](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-31...6.9.12-32) - 2021-12-04

### Commits

- ... [`60be1a6`](https://github.com/ImageMagick/ImageMagick6/commit/60be1a6c9698fc970c087b5384da19829b8fb386)
- https://github.com/ImageMagick/ImageMagick/issues/4501 [`fa5c3aa`](https://github.com/ImageMagick/ImageMagick6/commit/fa5c3aa6c111b8c4c83d945e992da95200dbdba6)
- revert memory leak patch [`e735d88`](https://github.com/ImageMagick/ImageMagick6/commit/e735d88c251a4c7ef60c39ae3322fc7b4cbb50f9)
- https://github.com/ImageMagick/ImageMagick/issues/4501 [`936332e`](https://github.com/ImageMagick/ImageMagick6/commit/936332e6b6a5e6105f02b2d9232bcbeafa681eb3)
- https://github.com/ImageMagick/ImageMagick/issues/4501 [`2a29e35`](https://github.com/ImageMagick/ImageMagick6/commit/2a29e35480271e14a0961492867e9d246e64cc05)
- eliminate compiler warning [`63f5b43`](https://github.com/ImageMagick/ImageMagick6/commit/63f5b4329181e70cff1a646229dc3b3ba5a40d69)
- pending release [`be1bc1d`](https://github.com/ImageMagick/ImageMagick6/commit/be1bc1d9650b4530a037d7c2d58d1a5a4b73f04e)
- ... [`c611e8f`](https://github.com/ImageMagick/ImageMagick6/commit/c611e8f5102bbcf20ac0a4fd3e7e719779c60fd9)
- ASAN returns false positives for OMP [`976dba6`](https://github.com/ImageMagick/ImageMagick6/commit/976dba67f1a4352d838a2a9f823812892f8230b5)
- pending release [`3bf73bf`](https://github.com/ImageMagick/ImageMagick6/commit/3bf73bf7e3f846dd6d3e20b843e8a34e8f4f7589)
- pending release [`9e8e460`](https://github.com/ImageMagick/ImageMagick6/commit/9e8e460e7ef26ab6f5666c7292f7b82752a09b7d)
- https://github.com/ImageMagick/ImageMagick/issues/4512 [`4c0fcf3`](https://github.com/ImageMagick/ImageMagick6/commit/4c0fcf39fd51f2c89832767e1befaeda7ff86097)
- pending release [`1832b1d`](https://github.com/ImageMagick/ImageMagick6/commit/1832b1d334ca00e66ad6ff5f115750692cb6b3b7)
- Added check for invalid size. [`94f76dd`](https://github.com/ImageMagick/ImageMagick6/commit/94f76dd2f760241bec51e7d66873e77a58d812ba)
- https://github.com/ImageMagick/ImageMagick/issues/4535 [`9a7d07d`](https://github.com/ImageMagick/ImageMagick6/commit/9a7d07d8b22098210a47cabb99cb58de599bb5ba)
- Added missing checks for the return value of the exr methods. [`5beeab8`](https://github.com/ImageMagick/ImageMagick6/commit/5beeab8a1297dbae1f05f88aeffe26278b744a6f)
- close input file if early exit on exception [`fd51385`](https://github.com/ImageMagick/ImageMagick6/commit/fd513853ac20e6ae784a795fff41cacfe8b54e73)
- https://github.com/ImageMagick/ImageMagick/discussions/4529 [`e35c98c`](https://github.com/ImageMagick/ImageMagick6/commit/e35c98c5ab111284b198d0022ed479d0e6ecef3c)
- pending release [`b5525d6`](https://github.com/ImageMagick/ImageMagick6/commit/b5525d640ea48befa9cfb4e154672d4076f06aec)

## [6.9.12-31](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-30...6.9.12-31) - 2021-11-21

### Commits

- eliminate possible divide by zero [`8c80027`](https://github.com/ImageMagick/ImageMagick6/commit/8c80027ca8d6c84c3ed815059bbf353eb8dc2d58)
- ... [`9e6a637`](https://github.com/ImageMagick/ImageMagick6/commit/9e6a63782e4d22786b82b1db6575181724fdb4f1)
- Removed unnecessary define. [`6722a79`](https://github.com/ImageMagick/ImageMagick6/commit/6722a798f2b4385a293555675be8967890448b38)
- Corrected OpenCL define checks. [`149fb8a`](https://github.com/ImageMagick/ImageMagick6/commit/149fb8a345ccb58cc70d3252be5d0f7cf6850d64)
- pending release [`4976493`](https://github.com/ImageMagick/ImageMagick6/commit/49764932cdb7e0ac966828ce15a819d85ccbeae3)

## [6.9.12-30](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-29...6.9.12-30) - 2021-11-20

### Commits

- ... [`3b2a005`](https://github.com/ImageMagick/ImageMagick6/commit/3b2a005a5a58698d9cb99e48d46ce19d19abfd39)
- https://github.com/ImageMagick/ImageMagick6/issues/168 [`9a70911`](https://github.com/ImageMagick/ImageMagick6/commit/9a70911bc8b3c6f3a49bb54766cfba0e69f2a2fe)
- https://github.com/ImageMagick/ImageMagick6/issues/168 [`7599dd9`](https://github.com/ImageMagick/ImageMagick6/commit/7599dd92e8ad19993a2eb27a2b5103d853bce57f)
- mitigate UBSAN alerts [`1219eac`](https://github.com/ImageMagick/ImageMagick6/commit/1219eac5d3bfb796753597f37412df567f629c08)
- mitigate UBSAN alerts [`99841ed`](https://github.com/ImageMagick/ImageMagick6/commit/99841edc96458bad24754b587de79693da67224b)
- mitigate UBSAN alerts [`a4dec0c`](https://github.com/ImageMagick/ImageMagick6/commit/a4dec0cbdeb1ed2acf79e8efe664cdb2348e524b)
- destroy image list rather than just the first image [`c42cd7c`](https://github.com/ImageMagick/ImageMagick6/commit/c42cd7c143e501aff4d624a2591e7f26ee5d5ce9)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=41172 [`5f77de4`](https://github.com/ImageMagick/ImageMagick6/commit/5f77de42c37c184e6db6bbbad52a34070c5a7a2d)
- https://github.com/ImageMagick/ImageMagick/issues/4495 [`d46d0c6`](https://github.com/ImageMagick/ImageMagick6/commit/d46d0c647aa67bcfffec5dbd456c24b9c66de66e)
- check for NULL index channel [`f63a211`](https://github.com/ImageMagick/ImageMagick6/commit/f63a2117ba05da426d996c0aee92e5b0c7b1f852)
- check if indexes are null [`23bd057`](https://github.com/ImageMagick/ImageMagick6/commit/23bd0570ebb0b845aa62e0c66dd7d822594201ea)
- eliminate compiler warning [`7864d48`](https://github.com/ImageMagick/ImageMagick6/commit/7864d48ddb52c490484a890eea21717cab01c61c)
- check for NULL indexes [`3644f40`](https://github.com/ImageMagick/ImageMagick6/commit/3644f40f41d1bf1134e1d6fcd1f227436d045945)
- check for NULL indexes [`e008625`](https://github.com/ImageMagick/ImageMagick6/commit/e00862551327e0b2c4362d6d8f1b78bb4f3496af)
- pending release [`506ae2c`](https://github.com/ImageMagick/ImageMagick6/commit/506ae2c2e2d4bbb07d4ba4075d06aadccbc675fd)
- less aggressive sanity check [`dda7d0b`](https://github.com/ImageMagick/ImageMagick6/commit/dda7d0bb7d4f675f652fea20dff66778fb2bc88b)
- pending release [`1864067`](https://github.com/ImageMagick/ImageMagick6/commit/1864067f7083a965bc4c4f3ac36ab6976d80a831)

## [6.9.12-29](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-28...6.9.12-29) - 2021-11-14

### Commits

- ... [`c66229f`](https://github.com/ImageMagick/ImageMagick6/commit/c66229fb1a73213f392752050d49084d32032aec)
- latest docs [`f624d40`](https://github.com/ImageMagick/ImageMagick6/commit/f624d406e79ce1d5f600a1ff569bf02d6eccf4b2)
- Use CheckMergedImageAlpha when layer size is zero. [`b614db7`](https://github.com/ImageMagick/ImageMagick6/commit/b614db76102d0f4c38149d2b6c63e091bc975b6b)
- ... [`4efb23e`](https://github.com/ImageMagick/ImageMagick6/commit/4efb23ee93a2026434e5b0253ddb9c3622c1b1ab)
- pending release [`4dbdd3b`](https://github.com/ImageMagick/ImageMagick6/commit/4dbdd3bd7d4cb95bc883010d70d0e31d69308536)
- ... [`8867bad`](https://github.com/ImageMagick/ImageMagick6/commit/8867bada8703071aa5356240d677b2ac1069ff3e)
- ... [`04c02b3`](https://github.com/ImageMagick/ImageMagick6/commit/04c02b3ad4ae57a28c87a094fd72f153b6dc49bb)
- Corrected detection of the CMYK colorspace. [`af56076`](https://github.com/ImageMagick/ImageMagick6/commit/af56076082b5703d65f754a501876d082743a0ab)
- Improved detection of %%. [`cddc5be`](https://github.com/ImageMagick/ImageMagick6/commit/cddc5be6a7150e9c47fd155b402fc896e1d9d0b6)
- early exit on exception [`b272aca`](https://github.com/ImageMagick/ImageMagick6/commit/b272acab91444f2115099fe51ee6c91bb4db5d50)
- https://github.com/ImageMagick/ImageMagick/issues/4452 [`ba084f6`](https://github.com/ImageMagick/ImageMagick6/commit/ba084f6bda2edbacf1df824bb214728234ffaa86)
- pending release [`efe0cae`](https://github.com/ImageMagick/ImageMagick6/commit/efe0caec013e87837c29a83e57e5ea7397ce8645)

## [6.9.12-28](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-27...6.9.12-28) - 2021-10-29

### Commits

- ... [`dd1dc33`](https://github.com/ImageMagick/ImageMagick6/commit/dd1dc3392ee1ec775f9d53d2fe306e458dadaef2)
- ... [`e10fc76`](https://github.com/ImageMagick/ImageMagick6/commit/e10fc76ab4c7850547271a73d1b1c7ebebb691be)
- Fix stack overflow when parsing malicious ps image file. [`f74b2b1`](https://github.com/ImageMagick/ImageMagick6/commit/f74b2b19d13df6b61b5ede33aa7249dcb0f496a5)
- cosmetic [`d480691`](https://github.com/ImageMagick/ImageMagick6/commit/d480691c7d0ad3f16ff94148e781cbaff05ed1be)
- pending release [`af2ee30`](https://github.com/ImageMagick/ImageMagick6/commit/af2ee30d2201829812864d7d8aadee0e46cd5d91)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=40451 [`ba7e11c`](https://github.com/ImageMagick/ImageMagick6/commit/ba7e11c5ea554317c28977ff6e5afc4f050a7ae1)
- pending release [`f59af4f`](https://github.com/ImageMagick/ImageMagick6/commit/f59af4f713acf87b7279e68c01ac9579fea8793a)
- pending release [`0ca0004`](https://github.com/ImageMagick/ImageMagick6/commit/0ca000449de02d87e3fccba10255472417a4d3dc)
- ... [`4b5c30c`](https://github.com/ImageMagick/ImageMagick6/commit/4b5c30c0b879dc4c670c27f53721df60896724c2)
- pending release [`1898d52`](https://github.com/ImageMagick/ImageMagick6/commit/1898d52023601f8ea5bdb583f9dd2b3a435572cb)

## [6.9.12-27](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-26...6.9.12-27) - 2021-10-25

### Commits

- ... [`60fcc24`](https://github.com/ImageMagick/ImageMagick6/commit/60fcc24991c45628286b8a88ccd5983d4979626d)
- pending release [`b6fe79f`](https://github.com/ImageMagick/ImageMagick6/commit/b6fe79f95ebd91a0439cbb7adb4602c4d4aa154e)

## [6.9.12-26](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-25...6.9.12-26) - 2021-10-24

### Commits

- :1 [`cc76510`](https://github.com/ImageMagick/ImageMagick6/commit/cc765107a9c7e19607e7fd18feb89a22a563ebb4)
- ... [`c4b9474`](https://github.com/ImageMagick/ImageMagick6/commit/c4b94746cb97fc81b0b552e14f4e462449e567b5)
- Corrected versions in ChangeLog. [`7e972cc`](https://github.com/ImageMagick/ImageMagick6/commit/7e972cc7157ddaf638c8301945058970af0c114f)
- Correct more version numbers. [`b0a8b26`](https://github.com/ImageMagick/ImageMagick6/commit/b0a8b2655487ee5b6248897e5c955b8a44bfc790)
- https://github.com/ImageMagick/ImageMagick/issues/4372 [`2466e9a`](https://github.com/ImageMagick/ImageMagick6/commit/2466e9a94e42b2511ef7016259a72a714808f9fe)
- eliminate compiler warning [`8afbdbc`](https://github.com/ImageMagick/ImageMagick6/commit/8afbdbc36fe128383b4fce3374c080ac34177b15)
- https://github.com/ImageMagick/ImageMagick/issues/4378 [`c661299`](https://github.com/ImageMagick/ImageMagick6/commit/c661299cd1ff36d8783641cb4cffdffb0fd9041d)
- https://github.com/ImageMagick/ImageMagick/issues/4379 [`199a858`](https://github.com/ImageMagick/ImageMagick6/commit/199a8586fd1ab273b25dae3f75ff131f4b302ceb)
- ... [`6fe9741`](https://github.com/ImageMagick/ImageMagick6/commit/6fe9741ec186b9893bc87d39e83d0d705fe0fad5)
- adjust metrics is no longer sensitive to gravity [`6dc9251`](https://github.com/ImageMagick/ImageMagick6/commit/6dc9251f0dcc11d29dbb90f430431b553df46f35)
- test release [`01e79c2`](https://github.com/ImageMagick/ImageMagick6/commit/01e79c207608bb7eacd4b6710663213773684dcd)
- fix stack overflow when parsing malicious tiff image [`85a370c`](https://github.com/ImageMagick/ImageMagick6/commit/85a370c79afeb45a97842b0959366af5236e9023)
- pending release [`fd247de`](https://github.com/ImageMagick/ImageMagick6/commit/fd247de75a1f271474294cc97c09f291e58f2be3)
- ... [`7671137`](https://github.com/ImageMagick/ImageMagick6/commit/76711376db504e9c786426e9381021889b00590e)
- pending release [`adf4467`](https://github.com/ImageMagick/ImageMagick6/commit/adf446722724ea7cad8ebc6046e87df82aae4f05)
- slight performance optimization [`627cf43`](https://github.com/ImageMagick/ImageMagick6/commit/627cf4307b93d5185fe877db8ebb51236043f350)
- Revert adjustment of the y1 value [`122366e`](https://github.com/ImageMagick/ImageMagick6/commit/122366e570731f71c90e82f219c43d78864597a3)
- revert optimization [`07c8384`](https://github.com/ImageMagick/ImageMagick6/commit/07c838431ab2cd620daf1d43e35f8a3f0b23b7a5)
- pending release [`a85dee3`](https://github.com/ImageMagick/ImageMagick6/commit/a85dee3187419ab8c8dc1385b0be9bd9c51c731c)
- https://oss-fuzz.com/testcase-detail/6308942275805184 [`5c82207`](https://github.com/ImageMagick/ImageMagick6/commit/5c822075c884a488242d8d5558964a087cc9db99)
- pending release [`3430fb8`](https://github.com/ImageMagick/ImageMagick6/commit/3430fb87b5714e3d50717497be71a0531600da76)
- pending release [`175f33e`](https://github.com/ImageMagick/ImageMagick6/commit/175f33e13311562f51ae7b1631af65bb0ee29676)

## [6.9.12-25](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-24...6.9.12-25) - 2021-10-10

### Commits

- ... [`cfcd23e`](https://github.com/ImageMagick/ImageMagick6/commit/cfcd23ee92152228ba36ac12d6fc0a6ec34d41c0)
- https://github.com/ImageMagick/ImageMagick/discussions/4311 [`f6fdd03`](https://github.com/ImageMagick/ImageMagick6/commit/f6fdd03216d401b7e3b558218f7805b61d2cecc5)
- ... [`24961a9`](https://github.com/ImageMagick/ImageMagick6/commit/24961a9e25ac31b7ddd42eb8f1c130717971da16)
- https://github.com/ImageMagick/ImageMagick/issues/4314 [`c8bba5b`](https://github.com/ImageMagick/ImageMagick6/commit/c8bba5bf458c63486417c6f0084ce383c89d78b1)
- don't adjust metrics if gravity is undefined [`79c537c`](https://github.com/ImageMagick/ImageMagick6/commit/79c537c7bdfe0f71b4354ace4d9c9976c29b4c4a)
- Moved using namespace std after ImageMagick header files to fix issues when enabling ISO C++ 17 and ISO C17 [`2c96ab5`](https://github.com/ImageMagick/ImageMagick6/commit/2c96ab5d098fcf3d2002378355bc2ad3eaccaddf)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=39708 [`5569c6c`](https://github.com/ImageMagick/ImageMagick6/commit/5569c6cc38ea99d9cba667deaddf09ba1ec42005)
- fix ANSI compiler error [`94119fe`](https://github.com/ImageMagick/ImageMagick6/commit/94119febc83c74913017289e5060e1e5ccf378d4)
- ... [`48e52d0`](https://github.com/ImageMagick/ImageMagick6/commit/48e52d0ef0ce365a5a6e7c4d20cff582be835786)
- pending release [`af67f12`](https://github.com/ImageMagick/ImageMagick6/commit/af67f1234b95fcad2fc28560fb8136defc16108a)

## [6.9.12-24](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-23...6.9.12-24) - 2021-10-03

### Commits

- ... [`f4277c4`](https://github.com/ImageMagick/ImageMagick6/commit/f4277c460e804659535de8e2d8dd9507ab50bb2f)
- ... [`92194b2`](https://github.com/ImageMagick/ImageMagick6/commit/92194b2ac097619013e2be312b0121c0f75911a9)
- https://github.com/ImageMagick/ImageMagick/discussions/4227 [`1c5e41a`](https://github.com/ImageMagick/ImageMagick6/commit/1c5e41a934fd40ce86f37ecee6b54a6940183f1e)
- check return status [`cca5a6a`](https://github.com/ImageMagick/ImageMagick6/commit/cca5a6a3f9eacd6c5db570f90dcd3b73a30b2f59)
- ignore zero-length profiles [`94cc6fd`](https://github.com/ImageMagick/ImageMagick6/commit/94cc6fd1c2f3ad739903726ec7e63d31a2b3d747)
- Silence warning. [`32bda8b`](https://github.com/ImageMagick/ImageMagick6/commit/32bda8bb2132fad29eb6e175d3da92e45f9c25af)
- Fixed build error. [`78e0310`](https://github.com/ImageMagick/ImageMagick6/commit/78e03105e90cd4ac5cbe2970a31a13f66c1270bf)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=39091 [`a96f221`](https://github.com/ImageMagick/ImageMagick6/commit/a96f221bfa150943d0f63b6b44910c9abd8988b2)
- https://github.com/ImageMagick/ImageMagick/issues/4278 [`4748ccc`](https://github.com/ImageMagick/ImageMagick6/commit/4748ccc31888db1e8610084b611710e7e2dadbfe)
- Revert patch because this breaks font rendering for other fonts. [`c55ddb1`](https://github.com/ImageMagick/ImageMagick6/commit/c55ddb1d646b1540afafd918be89eef69d83b467)
- Use same code as IM7. [`770902f`](https://github.com/ImageMagick/ImageMagick6/commit/770902feba3806065e77e477d3b796a185e23a82)
- Correction of the bounds measurements. [`fd9443b`](https://github.com/ImageMagick/ImageMagick6/commit/fd9443b46cb0254f1a6908be2738950d402169ab)
- Adjust the x1 offset of the bounds to make sure a font is rendered inside the canvas. [`1746362`](https://github.com/ImageMagick/ImageMagick6/commit/17463624f35b293f5e1689b8039bcdae96bdd8d1)
- Whitespace. [`d338817`](https://github.com/ImageMagick/ImageMagick6/commit/d3388174b0603040fd78d681fa85cf1080bef493)
- cosmetic [`d2b4807`](https://github.com/ImageMagick/ImageMagick6/commit/d2b4807f8eefb98f150901f941f6a1eea892f867)
- Correct replacement of spaces that use more than one octet. [`1d59719`](https://github.com/ImageMagick/ImageMagick6/commit/1d597191bd1f45d05ff041c89b7e3f8759e9eaf5)
- Added extra check to prevent replacing a non-breaking space with a newline. [`6e82f6f`](https://github.com/ImageMagick/ImageMagick6/commit/6e82f6f182f585ecc1cc70cd3fe7c5adb6c6c5ea)
- Space pointer was still pointing to the old string. [`96f65f4`](https://github.com/ImageMagick/ImageMagick6/commit/96f65f410afee03d45563c5a5fe01f4496d9b581)
- Cosmetic. [`7467737`](https://github.com/ImageMagick/ImageMagick6/commit/74677375e48303e8d3355a1cd63bdd5ee0e90269)
- argument is const [`4137ebc`](https://github.com/ImageMagick/ImageMagick6/commit/4137ebce1e559a483bb50c6aab283a30a938d63d)
- pending release [`c15d3ae`](https://github.com/ImageMagick/ImageMagick6/commit/c15d3aef8ffe50174763ef00c5780e3d6c774232)

## [6.9.12-23](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-22...6.9.12-23) - 2021-09-18

### Commits

- ... [`a9b45b4`](https://github.com/ImageMagick/ImageMagick6/commit/a9b45b47282987cd0df488ed597e7b95179960c9)
- Don't set the resolution when the cropbox is used. [`de18836`](https://github.com/ImageMagick/ImageMagick6/commit/de18836f1e1ded1395df589e5977c1aa762b486c)
- Added link to advisory. [`bd43241`](https://github.com/ImageMagick/ImageMagick6/commit/bd432413b03d7eb01ad5dcb14127910b7f80ff4c)
- Give the buffer a proper size instead of "over allocating". [`ecd4719`](https://github.com/ImageMagick/ImageMagick6/commit/ecd4719848da7562d3724e6f1b7bf24d1b72f1fc)
- Added missing null checks. [`c7039d2`](https://github.com/ImageMagick/ImageMagick6/commit/c7039d20a2fe018f041e40459d722188293012c5)
- https://github.com/ImageMagick/ImageMagick/issues/4235 [`eef08cc`](https://github.com/ImageMagick/ImageMagick6/commit/eef08ccf4da69848a6f475806f23711577f62c9e)
- pending release [`54a7092`](https://github.com/ImageMagick/ImageMagick6/commit/54a70929c2ad8df2321d4b3fc9c7d1b986ddaa2b)
- Added missing bom. [`bd9fb58`](https://github.com/ImageMagick/ImageMagick6/commit/bd9fb58de3d9e3847054ccc7ff5caba72cd5877d)
- pending release [`4230c6e`](https://github.com/ImageMagick/ImageMagick6/commit/4230c6e6ab33f8ccaff98529284a6285dc10ec61)

## [6.9.12-22](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-21...6.9.12-22) - 2021-09-12

### Commits

- ... [`75e8372`](https://github.com/ImageMagick/ImageMagick6/commit/75e83721e27b60c7354cb3ec58205a9458999dd5)
- ... [`a6f6ee2`](https://github.com/ImageMagick/ImageMagick6/commit/a6f6ee269de56892b35ffbc03ab1accb4f593be9)
- Added yml to the .editorconfig [`06c089b`](https://github.com/ImageMagick/ImageMagick6/commit/06c089b3fe5438882d54cc2ad4dbc7394b852643)
- Use yaml template instead. [`edf63d3`](https://github.com/ImageMagick/ImageMagick6/commit/edf63d36a7af9468aa07ca2a4c7b9a98db67c1ec)
- Removed travis CI link. [`c3b1c13`](https://github.com/ImageMagick/ImageMagick6/commit/c3b1c1334809ad132dddbdfac91618b144fce796)
- Changed build status link [`412d49b`](https://github.com/ImageMagick/ImageMagick6/commit/412d49b2b2a733401a469b7e658a1113e720c550)
- Added donate badge. [`a3d7d3f`](https://github.com/ImageMagick/ImageMagick6/commit/a3d7d3f1926d060f8acb4417deed015a01efad01)
- https://github.com/ImageMagick/ImageMagick/issues/4059 [`9d97e95`](https://github.com/ImageMagick/ImageMagick6/commit/9d97e95150ed3cd7ddfc478248e48b9c0d40f56b)
- Minor optimization when nothing will change. [`bfbf998`](https://github.com/ImageMagick/ImageMagick6/commit/bfbf9988fd9350a6a4da03daa011539204eecdee)
- Removed newline. [`8cc488a`](https://github.com/ImageMagick/ImageMagick6/commit/8cc488aaca954aa26406678a0032f40561a3c9b4)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=38401 [`61c3f46`](https://github.com/ImageMagick/ImageMagick6/commit/61c3f4697b2915b10123c11b09f6cf58abe0c07e)
- Moved RSVG rendering to a separate method. [`1dc463e`](https://github.com/ImageMagick/ImageMagick6/commit/1dc463eb50f48b9bd4f06530021f4fe52376e5d4)
- Moved MSVG rendering to a separate method. [`a39da2b`](https://github.com/ImageMagick/ImageMagick6/commit/a39da2b112d2f36d78c5d79a821216385be7f8f3)
- Added extra policy check. [`899d06f`](https://github.com/ImageMagick/ImageMagick6/commit/899d06fb1a97083bddda51cc88abc0f79841667e)
- Fixed incorrect check when module is used as the domain in policy.xml that would allow the use of a disabled module. [`8cd2fcd`](https://github.com/ImageMagick/ImageMagick6/commit/8cd2fcd33460826628a7590dc3ce74d7785e1598)
- Added missing policy checks in RegisterStaticModules. [`69ea558`](https://github.com/ImageMagick/ImageMagick6/commit/69ea5587de17ef89476be47a3cb7f855c0355a74)
- Added early exists. [`005af2a`](https://github.com/ImageMagick/ImageMagick6/commit/005af2a1557c8b49bf1116c380435c8064f9f70c)
- Use AllPolicyRights instead. [`b60e171`](https://github.com/ImageMagick/ImageMagick6/commit/b60e17133b982d28816386b83174c2bc06dd39bd)
- Revert break to make it possible to use and allow list. [`10c0f5b`](https://github.com/ImageMagick/ImageMagick6/commit/10c0f5b31bbea82ebd219a0da201a99a2e874c52)
- Use the correct rights. [`428e685`](https://github.com/ImageMagick/ImageMagick6/commit/428e68597fa904d0bdc133d878e12acd7dc60fa3)
- Clean up the remaining PDF files if reading one of the files fails. [`3177df6`](https://github.com/ImageMagick/ImageMagick6/commit/3177df671ee3904bdfe09c05d297fa1580253e98)
- pending release [`83b8cb1`](https://github.com/ImageMagick/ImageMagick6/commit/83b8cb1d99f0f842be50007572c7ecdb588e292d)
- Also set RGB channels when reading the image (#167). [`4282b98`](https://github.com/ImageMagick/ImageMagick6/commit/4282b98eb645351ddf122faa67c94610718595dc)
- Added missing call to ConstrainColormapIndex. [`02ce9e1`](https://github.com/ImageMagick/ImageMagick6/commit/02ce9e1bbba067b2ebcc18d07456a22570cbf5f2)
- pending release [`be2ebac`](https://github.com/ImageMagick/ImageMagick6/commit/be2ebac260ba43ede0b3beb5820a5d6492c35481)
- https://github.com/ImageMagick/ImageMagick/issues/2579 [`843fd11`](https://github.com/ImageMagick/ImageMagick6/commit/843fd110d7d3b0fa5e00c553290739fde2778ab1)
- pending release [`9146746`](https://github.com/ImageMagick/ImageMagick6/commit/9146746f54a24775225e541edc58364ab13e0126)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=38573 [`c4bdacf`](https://github.com/ImageMagick/ImageMagick6/commit/c4bdacff93e145dc1dd282cca3b04127ceb71bf4)
- check for EOF [`b3bc44a`](https://github.com/ImageMagick/ImageMagick6/commit/b3bc44a3211edfa701075e3a178bb434050bb785)
- check for EOF [`ae88f07`](https://github.com/ImageMagick/ImageMagick6/commit/ae88f07cd31bdbb671270349abdc48d9ca6463fb)
- pending release [`f48b623`](https://github.com/ImageMagick/ImageMagick6/commit/f48b6233e976f56a499a49c55b5f3f26c11451f5)

## [6.9.12-21](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-20...6.9.12-21) - 2021-09-04

### Commits

- ... [`397b5c3`](https://github.com/ImageMagick/ImageMagick6/commit/397b5c32487efdc5eb7daf206c6317fb670bad16)
- ./configure --help no longer lists -disable-assert twice [`0aab306`](https://github.com/ImageMagick/ImageMagick6/commit/0aab3061aad8211bcec1eb0f4e479414c8a9a3f1)
- https://github.com/ImageMagick/ImageMagick/issues/4121 [`6ba45df`](https://github.com/ImageMagick/ImageMagick6/commit/6ba45df1e4c67d9897262a7ff5706eb404f2ea7f)
- tweak the bilevel image type [`473c7cd`](https://github.com/ImageMagick/ImageMagick6/commit/473c7cd850bdc40c2d1e8e72c4d3b073f1079138)
- https://github.com/ImageMagick/ImageMagick/issues/4105 [`3afc3bc`](https://github.com/ImageMagick/ImageMagick6/commit/3afc3bc9d97ec424bd92ab5c74f090586d91fa0b)
- Minor changes to the formatting of the parentheses. [`278a93e`](https://github.com/ImageMagick/ImageMagick6/commit/278a93e8940eff474a083b42dde39a0c7da1c85e)
- Use different values per channel for scale and translate. [`109e236`](https://github.com/ImageMagick/ImageMagick6/commit/109e236860e35212a90b5eb6b93a6662ca208233)
- Add -dPrinted=false to the Ghostscript options (#4019) [`5f82ea4`](https://github.com/ImageMagick/ImageMagick6/commit/5f82ea411e7e1190f2f7aed8a0b1c97a42b6bd58)
- Added .editorconfig [`afad655`](https://github.com/ImageMagick/ImageMagick6/commit/afad65584be6d6d25902599b44f4c20c9a747692)
- Use link for the Windows build instructions instead. [`d8da2c5`](https://github.com/ImageMagick/ImageMagick6/commit/d8da2c53bdc4a738017a8ba346ab523935878faa)
- Add -HDRI to the quantum in the version string when HDRI is enabled. [`423a801`](https://github.com/ImageMagick/ImageMagick6/commit/423a8014dfa4705ebd8ec057ea78d99c224871d7)
- https://oss-fuzz.com/testcase-detail/6502669439598592 [`995de33`](https://github.com/ImageMagick/ImageMagick6/commit/995de330310dd35531165d9471fe4d31e0fa79ae)
- pending release [`9eb3b4e`](https://github.com/ImageMagick/ImageMagick6/commit/9eb3b4ea7b66e515283c0f9b5158c0c2f368c324)
- initialize buffer before calling TIFFGetField() [`ce2f067`](https://github.com/ImageMagick/ImageMagick6/commit/ce2f0676f8766343ae2322ace7311a53c7ae6d97)
- Use UTC date as requested in #166. [`e0967ea`](https://github.com/ImageMagick/ImageMagick6/commit/e0967eae28b4594f08c0a443ee53ac15390cff4a)
- pending release [`c4ed7a2`](https://github.com/ImageMagick/ImageMagick6/commit/c4ed7a29cf8695a67341175a329532947bc50b54)

## [6.9.12-20](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-19...6.9.12-20) - 2021-08-22

### Commits

- ... [`aebaac6`](https://github.com/ImageMagick/ImageMagick6/commit/aebaac62a29393e35d3c20715056cb74f6792e13)
- timeb.h is deprecated [`827ba53`](https://github.com/ImageMagick/ImageMagick6/commit/827ba5310372558385feb91a03afda829928a25e)
- eliminate compiler warning [`1c9bcc6`](https://github.com/ImageMagick/ImageMagick6/commit/1c9bcc67803f7130afda8f2caa8bd8a5f1999dde)
- reset image structure magick member [`e2045ec`](https://github.com/ImageMagick/ImageMagick6/commit/e2045ec83b5f709decf50c762ceac843e749d52e)
- optimize on grayscale detection [`e38fce1`](https://github.com/ImageMagick/ImageMagick6/commit/e38fce1ef0f7b569ec664a4b228335e34e037ae0)
- grayscale images were not being written properly [`84e8b18`](https://github.com/ImageMagick/ImageMagick6/commit/84e8b18294907a1232b216d89a60008341dfbc5a)
- check if colorspace is incompatible before transforming it to sRGB [`fdf7e64`](https://github.com/ImageMagick/ImageMagick6/commit/fdf7e64ed09666a0c8f3588b47d302b01a7cdeaa)
- reduce memory moves [`0132164`](https://github.com/ImageMagick/ImageMagick6/commit/0132164f33ea82daf732f3923c2fb141cb834dcc)
- ... [`92a2023`](https://github.com/ImageMagick/ImageMagick6/commit/92a2023362cf5b2e31df3b9331015a3093deb65f)
- heap-based buffer overflow in TIFF coder (alert from Hunter Mitchell) [`e1fbcdf`](https://github.com/ImageMagick/ImageMagick6/commit/e1fbcdf3aad96d51db65c1601117396eac665a6d)
- heap-based buffer overflow in TIFF coder (alert from Hunter Mitchell) [`35b88c9`](https://github.com/ImageMagick/ImageMagick6/commit/35b88c9166bc1b3ce8893f52217bae00d8e2c532)
- heap-based buffer overflow in TIFF coder (alert from Hunter Mitchell) [`f90a091`](https://github.com/ImageMagick/ImageMagick6/commit/f90a091c7dd12cc53b0999bf49d1c80651534eea)
- eliminate improper assertion [`78c72ee`](https://github.com/ImageMagick/ImageMagick6/commit/78c72ee91c93c4d10f89de781a711bf4e53dfcd9)
- Whitespace [`4d1d0a6`](https://github.com/ImageMagick/ImageMagick6/commit/4d1d0a6a6adc8433126ec912c87336c797f92735)
- Only run the OpenCL benchmark when OpenCL is enabled. [`a04e6c4`](https://github.com/ImageMagick/ImageMagick6/commit/a04e6c49bdc19d9918d5a588ea3fd95f39dcd379)
- mean is already computed, don't compute it again [`b1a8609`](https://github.com/ImageMagick/ImageMagick6/commit/b1a86095382b696ffef5a286b3cdb2ecf1599683)
- the -format option now respects the -channel argument [`6dc7e94`](https://github.com/ImageMagick/ImageMagick6/commit/6dc7e946ad28bc74f0385f32409382d2c290f6c2)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=36990 [`9aa9170`](https://github.com/ImageMagick/ImageMagick6/commit/9aa91709d2b9ec1b98398e081e2fb67bb7e1718e)
- https://github.com/ImageMagick/ImageMagick/issues/4059 [`63037e7`](https://github.com/ImageMagick/ImageMagick6/commit/63037e7bbf33574513126f5aef0acf3416146a93)
- https://github.com/ImageMagick/ImageMagick/issues/4059 [`37b4985`](https://github.com/ImageMagick/ImageMagick6/commit/37b49851335e9df91de7cdf763d27768c85c69e3)
- https://github.com/ImageMagick/ImageMagick/issues/4059 [`54df923`](https://github.com/ImageMagick/ImageMagick6/commit/54df923634871204a7a371b9523ab63d67cc37d1)
- https://github.com/ImageMagick/ImageMagick/issues/4059 [`41c9434`](https://github.com/ImageMagick/ImageMagick6/commit/41c9434f427bcbba9163f4550cd034a6d8363fb9)
- Use &amp; instead. [`8a23eb2`](https://github.com/ImageMagick/ImageMagick6/commit/8a23eb2603186c704f30d4b2f17bdefa5d6822d3)
- stop parsing after exception [`44c3bfc`](https://github.com/ImageMagick/ImageMagick6/commit/44c3bfc788dd4c94682093d480c514ab38543a2f)
- stop parsing on exception [`b915afb`](https://github.com/ImageMagick/ImageMagick6/commit/b915afb73148a8da5bca4a018a43c0432873d7fc)
- pending release [`bf9a427`](https://github.com/ImageMagick/ImageMagick6/commit/bf9a4278c183d2713894d0ff1d4e97232cd2d70e)
- pending release [`4e5510e`](https://github.com/ImageMagick/ImageMagick6/commit/4e5510e020300678a4ea20a4e35348444981cba5)
- Use new solution that is already upgrade to VS2019. [`b9ca6d9`](https://github.com/ImageMagick/ImageMagick6/commit/b9ca6d96820f7f2278515f6bfb26b72c42e1338b)
- pending release [`d49be7f`](https://github.com/ImageMagick/ImageMagick6/commit/d49be7fbb7667ec214cd00a16145d7f4e3f1606e)
- pending release [`1e43b29`](https://github.com/ImageMagick/ImageMagick6/commit/1e43b291a5825520860b92acb3f7b52ba6145805)
- pending release [`0f1b20c`](https://github.com/ImageMagick/ImageMagick6/commit/0f1b20cf7eaa687847c1da3356961eb44e807911)

## [6.9.12-19](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-18...6.9.12-19) - 2021-07-18

### Commits

- ... [`45df407`](https://github.com/ImageMagick/ImageMagick6/commit/45df407647856e7b5750767e49885b2f32a29c36)
- https://github.com/ImageMagick/ImageMagick/issues/3896 [`f939ee0`](https://github.com/ImageMagick/ImageMagick6/commit/f939ee00031464bd30cc69dcab8777f39ee8fbb8)
- ... [`3b491b8`](https://github.com/ImageMagick/ImageMagick6/commit/3b491b852a6f692ebc3ace6fee8ceb7ceb0adde9)
- remove virtual canvas offset from similarity image [`1f974fd`](https://github.com/ImageMagick/ImageMagick6/commit/1f974fd9eb285da31989e97d51fca67648643ef2)
- ... [`b847557`](https://github.com/ImageMagick/ImageMagick6/commit/b847557488c072763c2a0ecf62d0cfac5748353b)
- ... [`d09e86f`](https://github.com/ImageMagick/ImageMagick6/commit/d09e86f7d23784a2e8156ad7341a4221f0034d83)
- ... [`d881b80`](https://github.com/ImageMagick/ImageMagick6/commit/d881b800c7f768bb5926e0ad730401bd866865cc)
- Fixed writing the iptc information when it is not stored as long. [`f4feb3e`](https://github.com/ImageMagick/ImageMagick6/commit/f4feb3eef7d1013f90babd21dee51736a21be1b2)
- https://github.com/ImageMagick/ImageMagick/issues/3951 [`e924a55`](https://github.com/ImageMagick/ImageMagick6/commit/e924a55afa85eff1780ad78d875f6429a50c4c11)
- call wand genesis / terminus rather than core [`c4f26fb`](https://github.com/ImageMagick/ImageMagick6/commit/c4f26fbfd50bdb47397977758dc770f92b35a4bd)
- pending release [`c0e73a4`](https://github.com/ImageMagick/ImageMagick6/commit/c0e73a46b330d6f58dd0f5bb5ecf7c9287812acb)
- revert; keep CoreGenesis/CoreTerminus pairs; destroy wand ids [`2f3cc2c`](https://github.com/ImageMagick/ImageMagick6/commit/2f3cc2cf8339f1defd4215efcb320119de6ac1df)
- install wand.h header that defines DestroyWandIDs() [`c2d788c`](https://github.com/ImageMagick/ImageMagick6/commit/c2d788c52ab9824c938af0a85ae83281d4c9c0a4)
- pending release [`5b9a9db`](https://github.com/ImageMagick/ImageMagick6/commit/5b9a9dbbe0c5b1654ff3185dee96fae0f0514295)
- call MagickWandGenesis()/MagickWandTerminus() [`64aef14`](https://github.com/ImageMagick/ImageMagick6/commit/64aef14cc75b3bc0af31bc417060d79dfb6194e0)
- pending release [`1015767`](https://github.com/ImageMagick/ImageMagick6/commit/1015767a1429e3fa67b63853dc67d625171812c1)
- pending release [`e28afaa`](https://github.com/ImageMagick/ImageMagick6/commit/e28afaa4eb6f184689c218debe9ba4874b9f727b)

## [6.9.12-18](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-17...6.9.12-18) - 2021-07-17

### Merged

- uses the PerceptibleReciprocal() to prevent the divide-by-zero from occurring [`#3194`](https://github.com/ImageMagick/ImageMagick6/pull/3194)

### Commits

- ... [`74f450e`](https://github.com/ImageMagick/ImageMagick6/commit/74f450e153dccb64bc254fca89318b00f6dd0eda)
- Use the new issue templates. [`7c853af`](https://github.com/ImageMagick/ImageMagick6/commit/7c853afa3be12dfff22b34f0d2ddaf15180e66d9)
- system() is not supported under IOS [`b9f3577`](https://github.com/ImageMagick/ImageMagick6/commit/b9f3577b509808187fcb9b4a8955d6327bcd0e09)
- Removed checklist. [`bc06359`](https://github.com/ImageMagick/ImageMagick6/commit/bc06359cf59e33b88ba0199f01ed4b5f1bbe8f6b)
- Make it more clear that no memory is leaking. [`7f0b16c`](https://github.com/ImageMagick/ImageMagick6/commit/7f0b16c0578766a578cdaa686e891b4812d17848)
- The predictor tag should only be set for specific compression types. [`96c9b70`](https://github.com/ImageMagick/ImageMagick6/commit/96c9b7032d4b5cc3703cc32a1d59ab8c64a6a289)
- set imaginary component of the complex conjugate to -Ai [`f6b610f`](https://github.com/ImageMagick/ImageMagick6/commit/f6b610f6370b5140b86e50854a0b72dfc4d0dff0)
- Added raqm to the autolinking list. [`756685f`](https://github.com/ImageMagick/ImageMagick6/commit/756685f4111943499a530c4bcf84b55964b8ba00)
- Added option to peek in the byte buffer. [`63bc851`](https://github.com/ImageMagick/ImageMagick6/commit/63bc85166df5b0c14562687252d8050cee1a73fb)
- Fixed parsing the spot colors of a postscript document. [`ce84a88`](https://github.com/ImageMagick/ImageMagick6/commit/ce84a88592408d25533cd63a58ba7ee1b2b7c4cd)
- prevent blow up when standard deviation is 0 [`033df67`](https://github.com/ImageMagick/ImageMagick6/commit/033df67ae2d4ef2dc13952bfc48cbc5bef4b1686)
- optimize grayscale detection [`ec9feab`](https://github.com/ImageMagick/ImageMagick6/commit/ec9feabc987df9781c4e89f2ce014b75b02bfd0d)
- check for zero demoninator [`e110b81`](https://github.com/ImageMagick/ImageMagick6/commit/e110b81fd38b2e15dc7495699de53df51f4ade91)
- https://github.com/ImageMagick/ImageMagick/issues/3925 [`cd274e4`](https://github.com/ImageMagick/ImageMagick6/commit/cd274e439e7bb49d18b1be7617d89f3be91b3188)
- Corrected getting the image dimensions when identifying a postscript file. [`d624b59`](https://github.com/ImageMagick/ImageMagick6/commit/d624b590d2b1a4dd2d9f6794d6c388ca7b9069db)
- Fixed copy paste mistake. [`0416173`](https://github.com/ImageMagick/ImageMagick6/commit/0416173677748e027ac772fa2094174a0a91b6d3)
- proper cast [`4ce1321`](https://github.com/ImageMagick/ImageMagick6/commit/4ce1321c497e76e07d6c785840a2c6a0d2c6dbd8)
- pending release [`83e0280`](https://github.com/ImageMagick/ImageMagick6/commit/83e0280d488f14cf73f1e85cbf6857a56438f2db)

## [6.9.12-17](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-16...6.9.12-17) - 2021-06-25

### Commits

- ... [`801ffbd`](https://github.com/ImageMagick/ImageMagick6/commit/801ffbdc1a221e7a9947d22efb81101ce7fb2289)
- ... [`c1cb4d2`](https://github.com/ImageMagick/ImageMagick6/commit/c1cb4d26d533aa137cc5280aa6370f8d61150a1c)
- ... [`8c99db4`](https://github.com/ImageMagick/ImageMagick6/commit/8c99db4d683f3fd1a4a89b85b3dc5c4b2c7295f4)
- fix memory corruption in ConcatenateStringInfo [`7b5d5d9`](https://github.com/ImageMagick/ImageMagick6/commit/7b5d5d943fec12ccd167a6fed11758c609cb3275)
- pending release [`fdb4ff6`](https://github.com/ImageMagick/ImageMagick6/commit/fdb4ff6575cb1012397a9a9e03f45924d56fd8fa)

## [6.9.12-16](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-15...6.9.12-16) - 2021-06-20

### Commits

- ... [`dafa983`](https://github.com/ImageMagick/ImageMagick6/commit/dafa983fea7c9b0160c375435c53e83bc436b3c8)
- ... [`8aea6ca`](https://github.com/ImageMagick/ImageMagick6/commit/8aea6ca9f5363b4f5d6caaaa1df2c87a4bc43c82)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=35322 [`40f9bcd`](https://github.com/ImageMagick/ImageMagick6/commit/40f9bcd0f47d24eae4a9c3d542273af586938695)
- https://github.com/ImageMagick/ImageMagick/issues/3844 [`fdf3836`](https://github.com/ImageMagick/ImageMagick6/commit/fdf38365635ec2e31d1c5294f1fb22a34917f2d4)
- pending release [`17d7b4b`](https://github.com/ImageMagick/ImageMagick6/commit/17d7b4bad2ca7fc7374164f1c40cb6f8282c4afb)
- ver allocate memory, typically used when concatentating strings [`73a59dc`](https://github.com/ImageMagick/ImageMagick6/commit/73a59dcd4eaae3a0cec565abda9c0dcb070c734a)
- ... [`d259da5`](https://github.com/ImageMagick/ImageMagick6/commit/d259da5de84df842780e79b5994a8d95b16c488c)
- Revert patch that automatically changes the image orientation. [`086c8ee`](https://github.com/ImageMagick/ImageMagick6/commit/086c8eebf8df72086f2370b1e5c9ec72becaf89a)
- Use the same typecast as in ImageMagick 7. [`d02e016`](https://github.com/ImageMagick/ImageMagick6/commit/d02e016daae2768e7abfc034c4b81d8fb3863617)
- pending release [`25aa96d`](https://github.com/ImageMagick/ImageMagick6/commit/25aa96dee935a052bd0b0893780bb5ea6bc4ecb4)
- pending release [`46762e1`](https://github.com/ImageMagick/ImageMagick6/commit/46762e1b539aba1bfc7f39f6027a23a7cf84d276)

## [6.9.12-15](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-14...6.9.12-15) - 2021-06-12

### Commits

- ... [`ece4978`](https://github.com/ImageMagick/ImageMagick6/commit/ece4978c35d73eee4eda064b8f429a6ad42a3bec)
- https://github.com/ImageMagick/ImageMagick/issues/3765 [`a8c277e`](https://github.com/ImageMagick/ImageMagick6/commit/a8c277e07d1a0c92179f830e9399ee7b8cc15931)
- Fixed memory leak when it failed to apply ICC color profile [`1d4b8f4`](https://github.com/ImageMagick/ImageMagick6/commit/1d4b8f499985f5b576b53b7b478a9c5ab82116d1)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=35024 [`cde1733`](https://github.com/ImageMagick/ImageMagick6/commit/cde173361e901f957e56640fe03f59e78d92168b)
- Write the number of channels of the color profile instead of the image (#2070). [`af88978`](https://github.com/ImageMagick/ImageMagick6/commit/af88978d2d35a047e1d7daa5a24df69e032db65a)
- Corrected writing the icc profile in a PDF file. [`5a73bdc`](https://github.com/ImageMagick/ImageMagick6/commit/5a73bdcc68d2b1a1a14df1324e0178778f7b9030)
- When the compression is OJPEG the colorspace should not be changed to YCbCr. [`24fa0a8`](https://github.com/ImageMagick/ImageMagick6/commit/24fa0a82bdde4bec9d85ba9a59aebc5d83f17743)
- https://github.com/ImageMagick/ImageMagick/issues/3818 [`4512ff0`](https://github.com/ImageMagick/ImageMagick6/commit/4512ff04e3bb51874129d4857734e235f52b974d)
- ... [`637a850`](https://github.com/ImageMagick/ImageMagick6/commit/637a850cf7f3d87e35041b82ee6305503b996ea6)
- https://github.com/ImageMagick/ImageMagick/issues/3786 [`ed858f9`](https://github.com/ImageMagick/ImageMagick6/commit/ed858f9af9797ddd07c818c0c84cfe1121d7fd9b)
- https://github.com/ImageMagick/ImageMagick/discussions/3813 [`dabbe44`](https://github.com/ImageMagick/ImageMagick6/commit/dabbe4450429779f526b9eb3ba29df9ff0653689)
- pending release [`15126f0`](https://github.com/ImageMagick/ImageMagick6/commit/15126f081300bac271947eb5dc21ecda6e85b070)
- https://github.com/ImageMagick/ImageMagick/issues/3818 [`b21457a`](https://github.com/ImageMagick/ImageMagick6/commit/b21457a7eb9cb4c2f7c497b36a8efdab71beb4e6)
- pending release [`f1893ff`](https://github.com/ImageMagick/ImageMagick6/commit/f1893ff113904f1062fbec74345e01fc708d0dba)

## [6.9.12-14](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-12...6.9.12-14) - 2021-05-31

### Commits

- ... [`14ea894`](https://github.com/ImageMagick/ImageMagick6/commit/14ea8946956a0b2be3c2c4acc73442ddfddee95a)
- https://github.com/ImageMagick/ImageMagick/discussions/3583 [`d780ce0`](https://github.com/ImageMagick/ImageMagick6/commit/d780ce0a931d809e4452b7b3c8181806baeb1e8c)
- ... [`5e392ec`](https://github.com/ImageMagick/ImageMagick6/commit/5e392ec12363fdfd8fe9b5d98bbead89f560dd78)
- ... [`e53f1fd`](https://github.com/ImageMagick/ImageMagick6/commit/e53f1fd02a97f521c4b26faf439b7b4bb55af58c)
- Added missing status checks. [`7b2c55c`](https://github.com/ImageMagick/ImageMagick6/commit/7b2c55c2280323956b7c70909775fc81cecf98bd)
- Fixed reading and writing the XMP chunk in a WebP image. [`62b736a`](https://github.com/ImageMagick/ImageMagick6/commit/62b736a9a6d7e736fabaaf728c8ecaaacadc2c7d)
- https://github.com/ImageMagick/ImageMagick/issues/3653 [`8e9b75e`](https://github.com/ImageMagick/ImageMagick6/commit/8e9b75ea13bf007724d5e6dd5625f9af7d6098fa)
- ... [`a792ea6`](https://github.com/ImageMagick/ImageMagick6/commit/a792ea62e0d72b86c2bb8502dec17f6e6d15c227)
- The image type should not be changed when the image already has the correct type. [`8f74220`](https://github.com/ImageMagick/ImageMagick6/commit/8f74220f4f1dfdb0841f055402f19e219348af56)
- update CSS [`502d738`](https://github.com/ImageMagick/ImageMagick6/commit/502d73855661295eec94519ea83a1c31a1804d1a)
- https://github.com/ImageMagick/ImageMagick/issues/3676 [`9d8e861`](https://github.com/ImageMagick/ImageMagick6/commit/9d8e86156f0f2c949623bfbd5c78d6c89a7c5467)
- pending release [`f4efad9`](https://github.com/ImageMagick/ImageMagick6/commit/f4efad954ad505c71d17fa40f94af691d1492555)
- Removed travis build. [`bdff671`](https://github.com/ImageMagick/ImageMagick6/commit/bdff671dc524e5faae69fa9dfe53b6af7d7d6ffc)
- https://github.com/ImageMagick/ImageMagick/pull/3685/ [`2ac82aa`](https://github.com/ImageMagick/ImageMagick6/commit/2ac82aa7f502c779cbabd7f7c06d39eedcbfb042)
- Moved definition of the define to this header file. [`5e2af4c`](https://github.com/ImageMagick/ImageMagick6/commit/5e2af4c542d0fee760eb9e2e0e3acd333156da0f)
- https://github.com/ImageMagick/ImageMagick/issues/3687 [`274d848`](https://github.com/ImageMagick/ImageMagick6/commit/274d8481b11054b0c15c3b118e0fd2bb57919119)
- pending release [`8947663`](https://github.com/ImageMagick/ImageMagick6/commit/89476634dafdafdf86573f75c6a34743d5805641)
- The path should not end in a backslash according to the MSDN documentation. [`8533847`](https://github.com/ImageMagick/ImageMagick6/commit/8533847ff7cfd9fb7de549d383179a65a7019ae9)
- Always use a wildcard in NTOpenDirectory. [`8305ee3`](https://github.com/ImageMagick/ImageMagick6/commit/8305ee3125b1d6cb9e6fb6978fae5a6ee6cb19f6)
- pending release [`6f1745f`](https://github.com/ImageMagick/ImageMagick6/commit/6f1745f5d593df4c3b98ec763c6b690abc1dec97)
- Silence mingw warnings. [`a4ec89d`](https://github.com/ImageMagick/ImageMagick6/commit/a4ec89d233d6d5e03d558b14989322db7ec5f413)
- Removed unused variable. [`5b44db7`](https://github.com/ImageMagick/ImageMagick6/commit/5b44db70ca28b8f88ab5f9104570e85c4e16e74f)
- ... [`abd606b`](https://github.com/ImageMagick/ImageMagick6/commit/abd606b33eae106296b660e047adfc1e933ef900)
- NULL color name is acceptable [`d5a3cf7`](https://github.com/ImageMagick/ImageMagick6/commit/d5a3cf7270d1ef509ef61a55f51e33c1e894854b)
- https://github.com/ImageMagick/ImageMagick/issues/3690 [`2f1c004`](https://github.com/ImageMagick/ImageMagick6/commit/2f1c00490617ce067d8319866c8022411d17f2a4)
- eliminate heap buffer overflow vulnerability, thanks to ZhangJiaxing (@r0fm1a) from Codesafe Team of Legendsec at Qi'anxin Group [`b307bca`](https://github.com/ImageMagick/ImageMagick6/commit/b307bcadcdf6ea6819951ac1786b7904f27b25c6)
- ... [`1b85287`](https://github.com/ImageMagick/ImageMagick6/commit/1b85287582cd72bcb128800d50878dd33a37ae65)
- https://github.com/ImageMagick/ImageMagick/pull/3749 [`6ba4b42`](https://github.com/ImageMagick/ImageMagick6/commit/6ba4b42dc9269f301952c1ec2dd0fb782834e00d)
- https://github.com/ImageMagick/ImageMagick/pull/3749 [`3233cab`](https://github.com/ImageMagick/ImageMagick6/commit/3233cab9b2a623626fe6d414b49dbe1a5b732a2d)
- update copyright [`e65639e`](https://github.com/ImageMagick/ImageMagick6/commit/e65639eace3619b600881c0722a9f5f28b2d0f46)
- ... [`c75ae77`](https://github.com/ImageMagick/ImageMagick6/commit/c75ae771a00c38b757c5ef4b424b51e761b02552)
- pending release [`7f8bf2f`](https://github.com/ImageMagick/ImageMagick6/commit/7f8bf2fe0325f577ab518fda227d068237065ac6)

## [6.9.12-12](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-11...6.9.12-12) - 2021-05-09

### Commits

- ... [`5ec7ae6`](https://github.com/ImageMagick/ImageMagick6/commit/5ec7ae6d969667bb78d238649dd422e8f8441436)
- ... [`dd9b62d`](https://github.com/ImageMagick/ImageMagick6/commit/dd9b62d7ca80ffe5eebb34befc727ab3e59dc10b)
- https://github.com/ImageMagick/ImageMagick/issues/3520 [`8aa401e`](https://github.com/ImageMagick/ImageMagick6/commit/8aa401e00e229f0cb55ac733b9aa03c8bab884f5)
- https://github.com/ImageMagick/ImageMagick/issues/3520 [`ed78be2`](https://github.com/ImageMagick/ImageMagick6/commit/ed78be2e62accb8ac0747fd2a72c9c52758b2f3a)
- pending release [`0d11539`](https://github.com/ImageMagick/ImageMagick6/commit/0d11539c266133971246eb2d0d49e626a43bcdf0)
- support dither:diffusion-amount define for Riemersma dithering [`0d0f402`](https://github.com/ImageMagick/ImageMagick6/commit/0d0f402452dda40667926548882d18d2d336e141)
- improve exception testing [`94026fb`](https://github.com/ImageMagick/ImageMagick6/commit/94026fbfb045d27576799d84ee63320ba7cbc7aa)
- ... [`a5fec66`](https://github.com/ImageMagick/ImageMagick6/commit/a5fec668b59d0a725d96d56fae1b4864073f5b86)

## [6.9.12-11](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-10...6.9.12-11) - 2021-05-04

### Commits

- Add full threshold map [`c9753f9`](https://github.com/ImageMagick/ImageMagick6/commit/c9753f9113014a3d0283e8e4332447e7d1e5ed52)
- fix names [`fbb8139`](https://github.com/ImageMagick/ImageMagick6/commit/fbb8139444e7d2debede07ceec91295243fb7619)
- ... [`3df3254`](https://github.com/ImageMagick/ImageMagick6/commit/3df32542e617b7df3291dded38a4825e926d8335)
- Use ExceptionInfo instead of letting libraw print to stderr. [`8462661`](https://github.com/ImageMagick/ImageMagick6/commit/8462661321389bab113b76bc74e0c27448914792)
- Replace tabs with spaces. [`b9d006e`](https://github.com/ImageMagick/ImageMagick6/commit/b9d006e0089fad6afab71528d34f00aa401e4023)
- Generate threshold-map.h instead. [`d4c3361`](https://github.com/ImageMagick/ImageMagick6/commit/d4c33614def7874b55607238f8fd83c8bbddea48)
- Corrected typo. [`3d0d0e0`](https://github.com/ImageMagick/ImageMagick6/commit/3d0d0e0564339cf93da53852fa50005b55890e87)
- Another attempt. [`816071e`](https://github.com/ImageMagick/ImageMagick6/commit/816071e70ea0dff2ec939dcb8a6b818f25e83d4f)
- Use magick instead of MagickCore. [`38f6779`](https://github.com/ImageMagick/ImageMagick6/commit/38f67793a6c37263e4aaffd8b9ef3c2510859836)
- ... [`c46cd9f`](https://github.com/ImageMagick/ImageMagick6/commit/c46cd9fe551b567fb7b40bba052d3502d00f0f30)
- fix Makefile separator exception [`0d00ae7`](https://github.com/ImageMagick/ImageMagick6/commit/0d00ae7e3afb9e5022bb00ba042b5e5ee71c6bc3)
- improve method name [`5d112e0`](https://github.com/ImageMagick/ImageMagick6/commit/5d112e0673ccc6f1632f6ff63c62d5a0bf6225e7)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=33831 [`307f11e`](https://github.com/ImageMagick/ImageMagick6/commit/307f11e997b452a2a0a24abcf52eff16f4e11119)
- https://github.com/ImageMagick/ImageMagick/issues/3468 [`5c22ac6`](https://github.com/ImageMagick/ImageMagick6/commit/5c22ac68a5077995db1ce40ddf37ea6ba14e3e29)
- ... [`2316ca6`](https://github.com/ImageMagick/ImageMagick6/commit/2316ca67f6a6997b131aef292d33a1c38ee5cccf)
- cosmetic [`f944c0e`](https://github.com/ImageMagick/ImageMagick6/commit/f944c0efc98c5c6f7d6858666d6e3b207ad73e03)
- ... [`b3f69a1`](https://github.com/ImageMagick/ImageMagick6/commit/b3f69a17a508788164a973ed8b9f10264b776f8b)
- Corrected check in the TIFF decoder. [`a260de2`](https://github.com/ImageMagick/ImageMagick6/commit/a260de22e0676d0497ff780f0ccdbb795c05141b)
- ... [`e670f7f`](https://github.com/ImageMagick/ImageMagick6/commit/e670f7fc527eafe79134eb81786179f1760d9ec7)
- https://github.com/ImageMagick/ImageMagick/issues/3520 [`caee165`](https://github.com/ImageMagick/ImageMagick6/commit/caee16574b1cce8f45cf01f63ea7a8988cbfe5fd)
- pending release [`1ba0774`](https://github.com/ImageMagick/ImageMagick6/commit/1ba077420bd1a69c5dd5daed2c4a8736240ef256)
- revert comments [`7d8a3b7`](https://github.com/ImageMagick/ImageMagick6/commit/7d8a3b762f3a9b1171d904da52293fe43cd8e0cb)
- pending release [`930161d`](https://github.com/ImageMagick/ImageMagick6/commit/930161d603e2b65f363a10ba142e2ac732e28302)

## [6.9.12-10](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-9...6.9.12-10) - 2021-04-28

### Merged

- Fix line endings in Geometry.h to LF. [`#149`](https://github.com/ImageMagick/ImageMagick6/pull/149)
- Fix incorrect client_data pointer being set in libjpeg context. [`#152`](https://github.com/ImageMagick/ImageMagick6/pull/152)

### Fixed

- Fix incorrect client_data pointer being set in libjpeg context. (#152) [`#150`](https://github.com/ImageMagick/ImageMagick6/issues/150) [`#151`](https://github.com/ImageMagick/ImageMagick6/issues/151)

### Commits

- ... [`c770f50`](https://github.com/ImageMagick/ImageMagick6/commit/c770f508dea2e72791845e745696092f3e794a58)
- ... [`99cbc9f`](https://github.com/ImageMagick/ImageMagick6/commit/99cbc9f2542b9857c8abe580870b2b7a59e60731)
- check image is not NULL before dereferencing [`5ee7e3e`](https://github.com/ImageMagick/ImageMagick6/commit/5ee7e3eae5a0f4c06969c5b99a0a605901c0eac1)
- pending release [`370ce4c`](https://github.com/ImageMagick/ImageMagick6/commit/370ce4c7e2f6c04a672ca0b5ebb05acb490e31e9)
- pending release [`fea001e`](https://github.com/ImageMagick/ImageMagick6/commit/fea001e31a471c1e6605aa6e6ae97fb554a0e784)

## [6.9.12-9](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-8...6.9.12-9) - 2021-04-24

### Commits

- ... [`99b82fe`](https://github.com/ImageMagick/ImageMagick6/commit/99b82feded146a666b808c977db248c0e78bc757)
- ... [`6fd9c48`](https://github.com/ImageMagick/ImageMagick6/commit/6fd9c48d18522fc739988c635b4f230f5a9553a9)
- Corrected ChangeLog. [`165f89f`](https://github.com/ImageMagick/ImageMagick6/commit/165f89f5c3cdd05a49c08c001187c8ccfb5d6e58)
- ... [`fb64736`](https://github.com/ImageMagick/ImageMagick6/commit/fb647360465898972581c5a44d92f05040c61bbf)
- ... [`969b02d`](https://github.com/ImageMagick/ImageMagick6/commit/969b02d7a66e0d74a5290183e334995586e4a3dd)
- ... [`181125f`](https://github.com/ImageMagick/ImageMagick6/commit/181125f67ecf9ac57adef1db861181d8d6adbe70)
- Corrected typo. [`c8c3cf8`](https://github.com/ImageMagick/ImageMagick6/commit/c8c3cf8a1d7f93de7127606e5ccc0f2068216322)
- ... [`878f631`](https://github.com/ImageMagick/ImageMagick6/commit/878f6315caa7d8b9f0c616147e71a2f2b25b1756)
- cosmetic [`3832fa1`](https://github.com/ImageMagick/ImageMagick6/commit/3832fa11c51785a611e7a7cc9c57073221ed7833)
- cosmetic [`47e1eab`](https://github.com/ImageMagick/ImageMagick6/commit/47e1eabbc7736a08aed1ec225a07357f65d19ede)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=33466 [`6cf7fd8`](https://github.com/ImageMagick/ImageMagick6/commit/6cf7fd8e84aedcdfb125120b230f5a1dcf781169)
- https://github.com/ImageMagick/ImageMagick/issues/3571 [`68a0f3f`](https://github.com/ImageMagick/ImageMagick6/commit/68a0f3f8b8e90190c78bc65403fc81192fb3da59)
- pending release [`e9740ab`](https://github.com/ImageMagick/ImageMagick6/commit/e9740ab2ea9ce835003966551ceebcae4ce16ff1)

## [6.9.12-8](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-7...6.9.12-8) - 2021-04-17

### Commits

- latest automake/autoconf [`1fb5916`](https://github.com/ImageMagick/ImageMagick6/commit/1fb5916a9010c993a6e77613310828e950c8959f)
- ... [`24030ed`](https://github.com/ImageMagick/ImageMagick6/commit/24030ed4a3009bac808989e4142942074308bd33)
- https://github.com/ImageMagick/ImageMagick/issues/3540 [`cd7f9fb`](https://github.com/ImageMagick/ImageMagick6/commit/cd7f9fb7751b0d59d5a74b12d971155caad5a792)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=33232 [`e699f55`](https://github.com/ImageMagick/ImageMagick6/commit/e699f559dfa912cf979893ab2cde9a0695218c30)
- https://github.com/ImageMagick/ImageMagick/issues/3537 [`5b0acdb`](https://github.com/ImageMagick/ImageMagick6/commit/5b0acdb5047fd322ea9ba3cbf7fe0718e3cda0af)
- https://github.com/ImageMagick/ImageMagick/issues/3549 [`0962d40`](https://github.com/ImageMagick/ImageMagick6/commit/0962d402b0af0d31d7267bb82f5460c53c54518e)
- https://github.com/ImageMagick/ImageMagick/issues/3520 [`0fcebd3`](https://github.com/ImageMagick/ImageMagick6/commit/0fcebd3e7a382830a8e56b98b3f67e06b4beadb3)
- write tiff colormapped images with an alpha channel as PHOTOMETRIC_RGB [`270494f`](https://github.com/ImageMagick/ImageMagick6/commit/270494f4ba392f230b2e816667416e5ac638e275)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=33350 [`0eccd35`](https://github.com/ImageMagick/ImageMagick6/commit/0eccd3556a8c456239a49f9064381ddc3e28476e)
- pending release [`e06e7ff`](https://github.com/ImageMagick/ImageMagick6/commit/e06e7ffbf1fa16039754558eac75a917bd827393)
- pending release [`e65db11`](https://github.com/ImageMagick/ImageMagick6/commit/e65db11090a270d7200adac080f623a7e75b1e96)

## [6.9.12-7](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-6...6.9.12-7) - 2021-04-11

### Merged

- fix perl syntax [`#144`](https://github.com/ImageMagick/ImageMagick6/pull/144)

### Commits

- ... [`b9a79ba`](https://github.com/ImageMagick/ImageMagick6/commit/b9a79ba19226ea0d5f81b61bb06b4b84f1bb7bcd)
- add a nonce to the signature generation [`d9600ec`](https://github.com/ImageMagick/ImageMagick6/commit/d9600ec25644b74d8be1bd432f280b2467c5e175)
- https://github.com/ImageMagick/ImageMagick/issues/3469 [`89f9691`](https://github.com/ImageMagick/ImageMagick6/commit/89f9691ab4fdfbb8cacbe6718a0e3b911982b0ff)
- https://github.com/ImageMagick/ImageMagick/issues/3469 [`75c05e1`](https://github.com/ImageMagick/ImageMagick6/commit/75c05e1a2b1763712a6d9ca9de237c0d9198647e)
- constrain sub-image list [`c4392ae`](https://github.com/ImageMagick/ImageMagick6/commit/c4392aee303fba6d5e813f8c2ae1b67c19b438cb)
- pending release [`e183af8`](https://github.com/ImageMagick/ImageMagick6/commit/e183af8ec3d8ce2d36e55beda63535052ff429ed)
- https://github.com/ImageMagick/ImageMagick/issues/3520 [`d4f04b4`](https://github.com/ImageMagick/ImageMagick6/commit/d4f04b4dfb783996b8f48c28d64c04ca8b8cd542)
- https://github.com/ImageMagick/ImageMagick6/issues/145 [`bc7f4f5`](https://github.com/ImageMagick/ImageMagick6/commit/bc7f4f54206f2053a45959e07704c7fc657e07aa)
- pending release [`b37dd2c`](https://github.com/ImageMagick/ImageMagick6/commit/b37dd2c732634c98c0beef253f3e03216cdb3fc0)
- https://github.com/ImageMagick/ImageMagick6/security/code-scanning/5?query=ref%3Arefs%2Fheads%2Fmain [`822e476`](https://github.com/ImageMagick/ImageMagick6/commit/822e4768034198ff0bcc41b551462295ca5baec6)
- https://github.com/ImageMagick/ImageMagick/issues/3520 [`bec4e2d`](https://github.com/ImageMagick/ImageMagick6/commit/bec4e2dabf96dd93ef0ca7bb384521acdcb4be1e)
- https://github.com/ImageMagick/ImageMagick/issues/3520 [`4c0a1d5`](https://github.com/ImageMagick/ImageMagick6/commit/4c0a1d5b7a230b84e2d420c592ce7bc355ebd785)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=33137 [`d94de13`](https://github.com/ImageMagick/ImageMagick6/commit/d94de132dce98a02dce3451dfc014d2286fa0d43)
- pending release [`8608fb1`](https://github.com/ImageMagick/ImageMagick6/commit/8608fb14228480364cda4080c1b2d3ed118d8b8d)
- ... [`e3ad231`](https://github.com/ImageMagick/ImageMagick6/commit/e3ad2313517d78a96b5bcfce1cd4ce37c9df8dba)
- ... [`0dbacf8`](https://github.com/ImageMagick/ImageMagick6/commit/0dbacf8c67e2788f3d13b6d9b442b72bfad2d055)
- revert patch [`3415a1d`](https://github.com/ImageMagick/ImageMagick6/commit/3415a1db1c4dfd8dc096f45c80f647e047da0cd8)
- pending release [`a14972b`](https://github.com/ImageMagick/ImageMagick6/commit/a14972b0323163a8a41e4e34213da2b277bce372)

## [6.9.12-6](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-5...6.9.12-6) - 2021-04-03

### Commits

- ... [`312df44`](https://github.com/ImageMagick/ImageMagick6/commit/312df44858c91c2b43c07f7bd7b61cea7332d31f)
- revert patch [`7703d3b`](https://github.com/ImageMagick/ImageMagick6/commit/7703d3b2c13e56cc7fe7ca004228e4e2d9b8067f)
- https://github.com/ImageMagick/ImageMagick/issues/3469 [`f8e4322`](https://github.com/ImageMagick/ImageMagick6/commit/f8e4322d169b0db00ca438c68bed0f4b5c5cabb5)
- https://github.com/ImageMagick/ImageMagick/issues/3469 [`fbecaf0`](https://github.com/ImageMagick/ImageMagick6/commit/fbecaf01e52c45465d2cfad8272bc578e469c953)
- pending release [`328bd1a`](https://github.com/ImageMagick/ImageMagick6/commit/328bd1a082a497239938910b4bff8b9bcc2cf768)
- Added missing null check. [`3f8f861`](https://github.com/ImageMagick/ImageMagick6/commit/3f8f8611b5cc7ba945eacc17ad801840b423c2c6)
- pending release [`0e74340`](https://github.com/ImageMagick/ImageMagick6/commit/0e74340c0adaa4370e971079c654fe405b57e607)
- https://github.com/ImageMagick/ImageMagick/security/code-scanning/30 [`cbc076e`](https://github.com/ImageMagick/ImageMagick6/commit/cbc076e95697faed2cfb1abcd60693b859135330)
- pending release [`7aab092`](https://github.com/ImageMagick/ImageMagick6/commit/7aab092ac4e77ec6d96fcfe74c53eaf3e6cf159d)
- prevent undefined-behavior issue reported by Hardik [`798838f`](https://github.com/ImageMagick/ImageMagick6/commit/798838f31c0112c10491bf2cf2a4d084be90e26f)
- pending release [`0f40ca2`](https://github.com/ImageMagick/ImageMagick6/commit/0f40ca207b30abfdd9e7c8868e6005c137c032b7)
- ... [`f2a5d86`](https://github.com/ImageMagick/ImageMagick6/commit/f2a5d8646472e4bc5cd0a18546db0a29d3b7795c)
- ... [`6c4bc78`](https://github.com/ImageMagick/ImageMagick6/commit/6c4bc786e900ef6ac08483d1cbe963ed3210eddf)
- pending release [`fd23993`](https://github.com/ImageMagick/ImageMagick6/commit/fd23993f35fbfb48353bdcf16da1767f13eb4e71)

## [6.9.12-5](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-4...6.9.12-5) - 2021-03-28

### Commits

- ... [`9a4bc34`](https://github.com/ImageMagick/ImageMagick6/commit/9a4bc34b4b985e7cf604dc58691e64c576d8c3bd)
- ... [`3e34aa8`](https://github.com/ImageMagick/ImageMagick6/commit/3e34aa8bdf295e0a9d1630eab6c45cbdc2d90d4f)
- fix c++ compiler exception [`0ec46fc`](https://github.com/ImageMagick/ImageMagick6/commit/0ec46fc805a5e7a4056b9614c7a994bfb39e53b0)
- eliminate C++ compile exception [`adda0fe`](https://github.com/ImageMagick/ImageMagick6/commit/adda0fe816d5098691aeec1b690d5178d4fe2a17)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=32322 [`c8f2595`](https://github.com/ImageMagick/ImageMagick6/commit/c8f25953ad1dd38a8b2d92738f0f742ad7e0bce7)
- latest beta release [`4981820`](https://github.com/ImageMagick/ImageMagick6/commit/498182048b243c1a20891edb69545832c8d17d80)
- Throw exception when no exception was raised but status was false (#3432). [`512668d`](https://github.com/ImageMagick/ImageMagick6/commit/512668dfd92b20d0d08b91d62b422d8262573281)
- https://github.com/ImageMagick/ImageMagick/issues/3428 [`4f47d5f`](https://github.com/ImageMagick/ImageMagick6/commit/4f47d5f43e7a776cb615433867945f86a556ae51)
- eliminate compiler warning [`6a5d357`](https://github.com/ImageMagick/ImageMagick6/commit/6a5d3575487487f2703383338bd17c8c25068f19)
- Disable OpenCL by default. [`9a5b074`](https://github.com/ImageMagick/ImageMagick6/commit/9a5b07493a639c063caaac334b2e664c2484df7d)
- fix handling of non-square images with -fft option [`ffa0d49`](https://github.com/ImageMagick/ImageMagick6/commit/ffa0d49a7556be8f5e9ebf9c14096e5a6102bff8)
- pending release [`8dc8e09`](https://github.com/ImageMagick/ImageMagick6/commit/8dc8e090e29c15161de42b62935b706a11e53477)
- pending release [`0be2e6a`](https://github.com/ImageMagick/ImageMagick6/commit/0be2e6a5063613c1ed795a863916ccc4481514ce)

## [6.9.12-4](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-3...6.9.12-4) - 2021-03-20

### Commits

- ... [`b7ed95d`](https://github.com/ImageMagick/ImageMagick6/commit/b7ed95d47f9a22fac2ab45769d7144fa988429ed)
- ... [`06d7298`](https://github.com/ImageMagick/ImageMagick6/commit/06d729858570caa124a24887cf723fe9679881d4)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=31872 [`2a56e44`](https://github.com/ImageMagick/ImageMagick6/commit/2a56e447a4a60a4b89fc8be0410a6db39d5e3de3)
- ... [`6d5f5d8`](https://github.com/ImageMagick/ImageMagick6/commit/6d5f5d8892fa316aad710521792d23fc7c783734)
- ... [`b13e1a8`](https://github.com/ImageMagick/ImageMagick6/commit/b13e1a86fdfc92aa7aa04bedbfa2e43f8c216667)
- https://github.com/ImageMagick/ImageMagick/discussions/3389 [`df6b526`](https://github.com/ImageMagick/ImageMagick6/commit/df6b5268be37616ab479b833fa78951a3bd4e8a1)
- ... [`fa69ed6`](https://github.com/ImageMagick/ImageMagick6/commit/fa69ed6f43ca120d9dfb5570330602de6badcf90)
- ... [`2204eb5`](https://github.com/ImageMagick/ImageMagick6/commit/2204eb57ae00b005b39165a47b8984eac01600a5)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=28891 [`f940ecb`](https://github.com/ImageMagick/ImageMagick6/commit/f940ecb921b7ab83da320334349f0cde1ff7f3e6)
- ... [`8a98e9f`](https://github.com/ImageMagick/ImageMagick6/commit/8a98e9ff9ee7455551aff6981b5d8503c507bfbc)
- avoid omp deadlock [`99ac197`](https://github.com/ImageMagick/ImageMagick6/commit/99ac1977da0883b78cd4e9b763f267e8bce389e8)
- pending release [`9b40562`](https://github.com/ImageMagick/ImageMagick6/commit/9b405621909fa2e67170178f795a115ddbe9e1db)
- ... [`21991f7`](https://github.com/ImageMagick/ImageMagick6/commit/21991f726e6a7505bf14f593033cc75533c8b783)
- pending release [`4ef5c73`](https://github.com/ImageMagick/ImageMagick6/commit/4ef5c73c83203e93b60a092e3bc74697a3310c7f)

## [6.9.12-3](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-2...6.9.12-3) - 2021-03-06

### Commits

- ... [`522b4a3`](https://github.com/ImageMagick/ImageMagick6/commit/522b4a3e5bd272873cdc81aa5fdffdc4c520d588)
- ... [`0370b8e`](https://github.com/ImageMagick/ImageMagick6/commit/0370b8e16fd3d7900005040d1663d676268ab1b3)
- slight adjustment to D65 illuminant [`1df11cf`](https://github.com/ImageMagick/ImageMagick6/commit/1df11cf4efb748e55d7366f46c6e3a847a742487)
- ... [`c51b249`](https://github.com/ImageMagick/ImageMagick6/commit/c51b2495fcfddc4b77908e2034ca1877c3b4a8bf)
- ... [`c498edc`](https://github.com/ImageMagick/ImageMagick6/commit/c498edcef55dea47d6c3c4f2636c467343299ec2)
- https://github.com/ImageMagick/ImageMagick/issues/3331 [`4eafab8`](https://github.com/ImageMagick/ImageMagick6/commit/4eafab89a2742865d770857a9d7434993f65ae6b)
- https://github.com/ImageMagick/ImageMagick/issues/3332 [`072d7b1`](https://github.com/ImageMagick/ImageMagick6/commit/072d7b10dbe74d1cf4ec0d008990c1a28c076f9e)
- https://github.com/ImageMagick/ImageMagick/issues/3333 [`366c970`](https://github.com/ImageMagick/ImageMagick6/commit/366c9708a7ca1256ee03d0d4addb2690ed42273f)
- https://github.com/ImageMagick/ImageMagick/issues/3334 [`1b3585f`](https://github.com/ImageMagick/ImageMagick6/commit/1b3585fb7adb4ced6609d58ce9c9feb43dffeaaf)
- https://github.com/ImageMagick/ImageMagick/issues/3335 [`ad492c7`](https://github.com/ImageMagick/ImageMagick6/commit/ad492c7ed4cf1cf285a7f6e2ee5a1e7cf24e73b2)
- https://github.com/ImageMagick/ImageMagick/issues/3336 [`5d33b8d`](https://github.com/ImageMagick/ImageMagick6/commit/5d33b8df73b0b1e40ee3fb7a334d28d929ae903c)
- https://github.com/ImageMagick/ImageMagick/issues/3337 [`4bf64fd`](https://github.com/ImageMagick/ImageMagick6/commit/4bf64fdd786728f372e8a701a663caa2774e7a23)
- https://github.com/ImageMagick/ImageMagick/issues/3338 [`4b5e026`](https://github.com/ImageMagick/ImageMagick6/commit/4b5e026c704d777efe9c2ead5dd68ca4fe3b2aa1)
- https://github.com/ImageMagick/ImageMagick/issues/3339 [`9a94877`](https://github.com/ImageMagick/ImageMagick6/commit/9a94877f7823b0b8a41d50638dd105229d91fa89)
- ... [`aa77b65`](https://github.com/ImageMagick/ImageMagick6/commit/aa77b657b123bf92843f96c610b85e1a389e8226)
- https://github.com/ImageMagick/ImageMagick/issues/3340 [`448f927`](https://github.com/ImageMagick/ImageMagick6/commit/448f9271ef479569fc46583b9aa4ddc5c962d867)
- pending release [`4a83315`](https://github.com/ImageMagick/ImageMagick6/commit/4a833158dd16e127e3ca042baed6b449630ec5e2)

## [6.9.12-2](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-1...6.9.12-2) - 2021-02-27

### Commits

- ... [`d945f43`](https://github.com/ImageMagick/ImageMagick6/commit/d945f43d0a103ec4af50816aab54ab3d3b574543)
- pending release [`588d323`](https://github.com/ImageMagick/ImageMagick6/commit/588d3230ca82c14f2de6e1e894311d9d4fcdb05d)
- check that image exists before we destroy it [`3418473`](https://github.com/ImageMagick/ImageMagick6/commit/34184739956fd739735d364ec5b15c2ee89568cf)
- ... [`4c08b0d`](https://github.com/ImageMagick/ImageMagick6/commit/4c08b0d598c753b5e0e5cc99be5c47c62323c6e0)
- pending release [`7d56434`](https://github.com/ImageMagick/ImageMagick6/commit/7d564341fe48bcab733188573e0e7d41674ad80c)
- pending release [`627cbd7`](https://github.com/ImageMagick/ImageMagick6/commit/627cbd7ea1e15ea2c9c0b7789e71b4e3a4aba962)
- fix compiler exception [`2e0bf51`](https://github.com/ImageMagick/ImageMagick6/commit/2e0bf51d81f5b9e5669699ace345330270991d00)
- pending release [`a9c2639`](https://github.com/ImageMagick/ImageMagick6/commit/a9c26392e18cf38d50621ab1719539cb7bf79a61)
- pending release [`c5e7a8b`](https://github.com/ImageMagick/ImageMagick6/commit/c5e7a8bbe66dd101d81f2bb16be232bfdb2d6d45)
- possible divide by zero + clear buffers [`e53e24b`](https://github.com/ImageMagick/ImageMagick6/commit/e53e24b078f7fa586f9cc910491b8910f5bdad2e)
- ... [`c8d0040`](https://github.com/ImageMagick/ImageMagick6/commit/c8d0040f8505ee16266dd57b3abda80d7f19fead)
- https://github.com/ImageMagick/ImageMagick/issues/3296 [`f1e68d2`](https://github.com/ImageMagick/ImageMagick6/commit/f1e68d22d1b35459421710587a0dcbab6900b51f)
- https://github.com/ImageMagick/ImageMagick/issues/3297 [`841138c`](https://github.com/ImageMagick/ImageMagick6/commit/841138cc282722a80e06977d683405a0cf1d78ef)
- cosmetic [`63d4768`](https://github.com/ImageMagick/ImageMagick6/commit/63d47686efceeeb4ee68daa01614aab76eecf07c)
- pending release [`309cf43`](https://github.com/ImageMagick/ImageMagick6/commit/309cf4397c0d3d9963af04aa9a56fe406446c656)
- https://github.com/ImageMagick/ImageMagick/issues/3317 [`bbb2dff`](https://github.com/ImageMagick/ImageMagick6/commit/bbb2dff98d0e97a0fe3f7e187855476c4590eed2)
- pending release [`abad074`](https://github.com/ImageMagick/ImageMagick6/commit/abad074de78b7a71afe8785b046885e0d16d75ce)
- https://github.com/ImageMagick/ImageMagick/issues/3320 [`b365302`](https://github.com/ImageMagick/ImageMagick6/commit/b3653027e9dc93d03917db602b83d15e70fee575)
- https://github.com/ImageMagick/ImageMagick/issues/3321 [`64c0cc2`](https://github.com/ImageMagick/ImageMagick6/commit/64c0cc234280544dabacc2b28017521851deebde)
- pending release [`eb69a8a`](https://github.com/ImageMagick/ImageMagick6/commit/eb69a8adc86a9b6a43d81f39b20a33f6a74d0013)

## [6.9.12-1](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-0...6.9.12-1) - 2021-02-21

### Commits

- ... [`7854805`](https://github.com/ImageMagick/ImageMagick6/commit/7854805a0e012213dad5b813e0de78799348f255)
- https://github.com/ImageMagick/ImageMagick/pull/3241 [`a19d95d`](https://github.com/ImageMagick/ImageMagick6/commit/a19d95d36f92b4266364fa6bbcea3e2cc0da712d)
- ... [`90510e0`](https://github.com/ImageMagick/ImageMagick6/commit/90510e0d208d498650ff6400fd405bdf1711e082)
- https://github.com/ImageMagick/ImageMagick/issues/3242 [`68ce241`](https://github.com/ImageMagick/ImageMagick6/commit/68ce2418726f566e43624f2ef1906d86746c8c2e)
- ... [`ea03af8`](https://github.com/ImageMagick/ImageMagick6/commit/ea03af8be5183f7a2fda2afad06e4e9a0a75893b)
- https://github.com/ImageMagick/ImageMagick/issues/3258 [`d285259`](https://github.com/ImageMagick/ImageMagick6/commit/d2852597c575cad62a65ed6edeeb8f5a36077add)
- ... [`268dc9f`](https://github.com/ImageMagick/ImageMagick6/commit/268dc9f87749044cc2de2e384128e6a4aed06669)
- ... [`f27cfb1`](https://github.com/ImageMagick/ImageMagick6/commit/f27cfb112338057f8fac5d6b016b3c69fb119b84)
- https://github.com/ImageMagick/ImageMagick/issues/3259 [`e6a300e`](https://github.com/ImageMagick/ImageMagick6/commit/e6a300ef2da27bcf767fdc9f43aea9bb73054b33)
- pending release [`05fc76c`](https://github.com/ImageMagick/ImageMagick6/commit/05fc76c3de140ab0ee5438b6be2d52bd5d8c323a)

## [6.9.12-0](https://github.com/ImageMagick/ImageMagick6/compare/6.9.11-62...6.9.12-0) - 2021-02-13

### Commits

- ... [`efb5ce8`](https://github.com/ImageMagick/ImageMagick6/commit/efb5ce8710604e7b86014a70e91d0372a3930b5b)
- bump minor release [`9f1d23f`](https://github.com/ImageMagick/ImageMagick6/commit/9f1d23fa325165a3426ba401b552e65397384e96)
- ... [`37d7edf`](https://github.com/ImageMagick/ImageMagick6/commit/37d7edfc6b4f7270a9539c14541a7d1d7358b6f2)
- cosmetic [`c8922ae`](https://github.com/ImageMagick/ImageMagick6/commit/c8922ae40e995f93654eeeeb90266867e4a00154)
- ... [`5d2e553`](https://github.com/ImageMagick/ImageMagick6/commit/5d2e553ff197322676b36c32da7079d2f6e41633)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=30839 [`6f604e9`](https://github.com/ImageMagick/ImageMagick6/commit/6f604e9cc06ea1291b6932fa7786c3a01306c424)
- ... [`dfd1d7f`](https://github.com/ImageMagick/ImageMagick6/commit/dfd1d7f43c68c4449a1e8666ea6087ff4ff17a05)
- ... [`0824c17`](https://github.com/ImageMagick/ImageMagick6/commit/0824c17ef4405641322bab4c9d717a30b6c80162)
- ... [`d886aa5`](https://github.com/ImageMagick/ImageMagick6/commit/d886aa509b6258e5312d28d4c106803491f31d92)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=30896 [`b322ab0`](https://github.com/ImageMagick/ImageMagick6/commit/b322ab0074a86cc62073a2b577ef21907f3111d7)
- update docs [`dab48ba`](https://github.com/ImageMagick/ImageMagick6/commit/dab48bafd2924a7349df9bdc1ce8c36fab893bc2)
- pending release [`769536d`](https://github.com/ImageMagick/ImageMagick6/commit/769536d06c3dc2171aac1ddd36a01edfa16b1977)
