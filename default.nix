let
    pkgs = (import <nixpkgs>) {};
    gcc = pkgs.gcc;
    stdenv = pkgs.stdenv;
in
    stdenv.mkDerivation {
        name = "helicopter";
        version = "0.0.1";
        src = ./.;
        phases = [ "unpackPhase" "buildPhase" "installPhase" ];

        buildPhase = ''
            ${gcc}/bin/gcc main.c -o main
        '';

        installPhase = ''
            mkdir -p $out/bin
            cp main $out/bin
        '';
    }