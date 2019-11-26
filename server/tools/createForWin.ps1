if(!(Test-Path cppTarget))
{
    $null = mkdir cppTarget
}

if(!(Test-Path golangTarget))
{
    $null = mkdir golangTarget
}

if(!(Test-Path ..\share\protocol))
{
    $null = mkdir ..\share\protocol
}

"-- Clean"

rm .\cppTarget\*
rm ..\share\protocol\*

Get-ChildItem .\protobuf\ | ForEach-Object -Process{
    Write-Host -NoNewline "-- Processing $_ ... "
    .\protoc.exe --proto_path=./protobuf/ --cpp_out=./cppTarget/ $_.name
    Write-Host "Done"
}

$null = New-Item ./protocol.pb.h

Get-ChildItem .\cppTarget\ -Filter *.h | ForEach-Object -Process{
    "#include <$_>" | Out-File -Append .\protocol.pb.h
}

"-- Copy to workspace"
mv .\protocol.pb.h .\cppTarget
cp .\cppTarget\* ..\share\protocol\


"All done, press [Enter] to finish"
 Read-Host | Out-Null
Exit