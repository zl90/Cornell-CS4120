use io
use conv

// An implementation of Turing's "bombe" attack on the Enigma cipher.
// Essentially, given a crib, it's possible to figure out the position of the
// rotors independently from plugboard (which has far more settings); this does
// involve brute force, but 26^3 is doable even with electromechanical means.
//
// (With rotors known, the plugboard can be reverse-engineered by hand...)
//
// The crib from which the loops were extracted as:
//             1         2        3          4         5
//   0123456789012345678901234567890123456789012345678901234567
//   theenigmacipheriscertainlystrongbutnotwithoutitsweaknesses
//   JCJYROSNHZXNTNGQPXHADDUSNKCGWZEOQFVLBDLFFDZQLJSHYMFNHWLYXY

toLower(c: int): int {
    if (c >= 'A' & c <= 'Z') { return c - 'A' + 'a' }
    return c
}

///////////////////////////////////////////////////////////////////////////////
/// Rotor

makeInverse(base: int[], inv: int[]) {
    c: int = 0
    while c < 26 {
        //We have c->base[c], inv has base[c] going to c.
        inv[base[c]] = c
        c = c + 1
    }
}

mkMatrix(n: int) : int[][]
{
    a: int[n][n]
    return a;
}

// Rotor encoding: forward map, reverse map, position
makeRotor(sig: int[]): int[][], int[][], int {
    forward:  int[][] = mkMatrix(26)
    backward: int[][] = mkMatrix(26)

    base: int[26]

    c: int = 0
    while c < 26 {
        cd: int = toLower(sig[c]) - 'a'
        base[c] = cd
        c = c + 1
    }

    inv: int[26]

    rot: int = 0
    while rot < 26 {
        //Fill in forward direction for this..
        c = 0
        while c < 26 {
            forward[rot][c] = base[c]
            c = c + 1
        }

        //Make inverse..
        makeInverse(base, inv)

        //Fill in backward
        c = 0
        while c < 26 {
            backward[rot][c] = inv[c]
            c = c + 1
        }

        //Simulate rotation..
        first:int = (base[0] - 1 + 26)%26
        pos:int = 1
        while pos < 26 {
            base[pos-1] = (base[pos] - 1 + 26)%26
            pos = pos + 1
        }

        base[25] = first

        rot = rot + 1
    }

    return forward, backward, 0
}

rotorEncryptForward(forward: int[][], backward: int[][], pos: int, letter: int): int {
    return forward[pos][letter]
}

rotorEncryptBack(forward: int[][], backward: int[][], pos: int, letter: int): int {
    return backward[pos][letter]
}

///////////////////////////////////////////////////////////////////////////////
/// Reflector

// This is just a permutation, so its state is an int[]

makeReflector(encoding: int[]): int[] {
    perm:int[26]

    //Extract the base permutation.
    c: int = 0
    while c < 26 {
        cd: int = toLower(encoding[c])-'a'
        perm[c] = cd
        c = c + 1
    }
    return perm
}

reflectorEncrypt(perm: int[], l:int): int {
    return perm[l]
}

main(a: int[][]) {
    loops: int[][] = {
     {12, 27, 6, 57, 25, 51, 52, -1},
     {12, 27, 6, 55, 25, 51, 52, -1},
     {12, 46, 47, -1},
     {12, 27, 6, 16, 11, 52, -1}
    }

    //Setup components
    r1f: int[][], r1b: int[][], r1p: int = makeRotor("EKMFLGDQVZNTOWYHXUSPAIBRCJ")
    r2f: int[][], r2b: int[][], r2p: int = makeRotor("AJDKSIRUXBLHWTMCQGZNPYFVOE")
    r3f: int[][], r3b: int[][], r3p: int = makeRotor("BDFHJLCPRTXVZNYEIWGAKMUSQO")
    mb: int[] = makeReflector("YRUHQSLDPXNGOKMIEBFZCWVJAT")

    pos: int = 0
    while (pos < 26*26*26) {
        //Guess where the first letter in the loop goes to..
        guess: int = 0
        while guess < 26 {
            allMatch: bool = true

            loop: int = 0
            while loop < length(loops) {
                l: int = guess
                //Try to go through the possible values..
                loopPos: int = 0
                while (loops[loop][loopPos] != -1) {
                    epos: int = pos + loops[loop][loopPos]

                    r1p = epos % 26
                    r2p = (epos/26)%26
                    r3p = epos/(26*26)%26
                    l = rotorEncryptForward(r1f, r1b, r1p, l)
                    l = rotorEncryptForward(r2f, r2b, r2p, l)
                    l = rotorEncryptForward(r3f, r3b, r3p, l)
                    l = reflectorEncrypt(mb, l)
                    l = rotorEncryptBack(r3f, r3b, r3p, l)
                    l = rotorEncryptBack(r2f, r2b, r2p, l)
                    l = rotorEncryptBack(r1f, r1b, r1p, l)
                    loopPos = loopPos + 1
                }

                if (l != guess)
                    allMatch = false

                loop = loop + 1
            } // while loop

            if allMatch {
                posStr: int[3]
                posStr[0] = (pos%26)+'A'
                posStr[1] = ((pos/26)%26)+'A'
                posStr[2] = ((pos/(26*26))%26)+'A'
                print ("MATCH At rotor pos:")
                print (posStr)
                print (" first comes in from:")
                guessStr:int[1]
                guessStr[0] = guess+'A'
                println(guessStr)
            }

            guess = guess + 1
        } // while guess

        pos = pos + 1
    } // while pos
}
