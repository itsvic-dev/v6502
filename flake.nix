{
  description = "v6502 - an experimental 6502 CPU emulator.";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    {
      self,
      nixpkgs,
      flake-utils,
    }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import nixpkgs { inherit system; };
      in
      {
        packages.default = pkgs.stdenv.mkDerivation rec {
          pname = "v6502";
          version = "1.0.0";
          src = ./.;
          nativeBuildInputs = with pkgs; [
            ninja
            meson
          ];
          doCheck = true;
          mesonFlags = [ "-Dtests=true" ];
        };

        devShells.default = pkgs.mkShell {
          nativeBuildInputs = with pkgs; [
            meson
            ninja
            cc65
            lcov
          ];
        };
      }
    );
}
