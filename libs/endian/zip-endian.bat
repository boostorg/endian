echo create zip file...
echo must be run from libs\endian directory

if $%1 == $ goto error

rmdir /s \temp\%1 2>nul
pushd .
mkdir \temp\%1
cd \temp\%1
md boost\endian\detail
md libs\endian\doc
md libs\endian\example
md libs\endian\test
popd
copy ..\..\boost\endian\*.hpp \temp\%1\boost\endian
copy ..\..\boost\endian\detail\*.hpp \temp\%1\boost\endian\detail
copy ..\..\libs\endian\index.html \temp\%1\libs\endian
copy ..\..\libs\endian\INSTALL \temp\%1\libs\endian
copy ..\..\libs\endian\doc\*.html \temp\%1\libs\endian\doc
copy ..\..\libs\endian\example\*.cpp \temp\%1\libs\endian\example
copy ..\..\libs\endian\test\Jamfile.v2 \temp\%1\libs\endian\test
copy ..\..\libs\endian\test\*.cpp \temp\%1\libs\endian\test

pushd \temp
zip -r %1.zip %1
popd
move \temp\%1.zip .

goto done

:error
echo usage: zip-endian version
echo   version will be used for both the .zip name and the highest level directory name
echo example: zip-endian endian-rc1

:done