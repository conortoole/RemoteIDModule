{ pkgs ? import (builtins.fetchTarball {
    url = "https://github.com/NixOS/nixpkgs/archive/3592b10a67b518700002f1577e301d73905704fe.tar.gz";
  }) {},
}:
let
  envname = "platformio-fhs";
  mypython = pkgs.python3.withPackages (ps: with ps; [ pip pykwalify ]);
in
(pkgs.buildFHSUserEnv {
  name = envname;
  targetPkgs = pkgs: (with pkgs; [
    platformio-core
    platformio
    mypython
    openocd
    udev
    usbutils
    segger-ozone
  ]);
  runScript = "env LD_LIBRARY_PATH= bash";
}).env

