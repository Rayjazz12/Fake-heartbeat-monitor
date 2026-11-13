# build.ps1 — builds the Fake Heartbeat Monitor Geode mod.
# Requires: Geode SDK installed and in PATH, VS 2022 C++ workload.
#
# Commands:
#   .\build.ps1           build the mod and package a .geode file
#   .\build.ps1 -Config Release
#   .\build.ps1 -Clean    remove build artifacts

param(
    [ValidateSet("Debug","Release")]
    [string]$Config = "Release",
    [switch]$Clean
)

$ErrorActionPreference = "Stop"

$Root = Split-Path -Parent $MyInvocation.MyCommand.Path
$Src = Join-Path $Root "src"
$Build = Join-Path $Root "build"
$Out   = Join-Path $Root "dist"

if ($Clean) {
    if (Test-Path $Build) { Remove-Item $Build -Recurse -Force }
    if (Test-Path $Out)   { Remove-Item $Out -Recurse -Force }
    Write-Host "Cleaned build artifacts."
    exit 0
}

Write-Host "Building Fake Heartbeat Monitor (`$Config) ..." -ForegroundColor Cyan

if (-not (Get-Command geode -ErrorAction SilentlyContinue)) {
    Write-Error "Geode CLI not found. Install it from https://github.com/geode-sdk/cli"
    exit 1
}

if (-not (Test-Path $Build)) { New-Item $Build -ItemType Directory | Out-Null }
Push-Location $Build
try {
    & geode cmake -G "Ninja" -DCMAKE_BUILD_TYPE=$Config $Src
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
    & ninja
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
}
finally {
    Pop-Location
}

New-Item $Out -ItemType Directory -Force | Out-Null
Get-ChildItem $Build -Filter "*.geode" | ForEach-Object {
    Copy-Item $_.FullName $Out -Force
}

Write-Host "Build done. Outputs in $Out" -ForegroundColor Green
