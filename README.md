Quantum-Foundations-Correlations
================================
`Updated Feb 2015`

Research notes and algorithm implementation on Quantum Foundations: `Correlations in C3` and `Blockcode Algorithm`, from Perimeter Institute, Summer 2014.

## Status
The work on Correlations is still ongoing; The Blockcode paper is complete.

`February 2015:` First implementation of the algorithm for binary BC in `C++`. See the `blockcode-cpp` folder.

Estimated complexity: `O( X!Y!2^(X-1) )` for BC of size `X`-rows and `Y`-columns. Code uses a more efficient method than presented in the paper to determine the class-equivalence of BCs. Speed: 1 Mil. BC of 3-columns checked in 1.5 seconds. ALso includes a parser from Fripertinger's coefficient form of BC.

`March 2015:` Initial idea for the Paradox-algorithm in binary BC. May attempt implementation soon.

## Credits
Original work on Correlation is due to Wah Loon Keng, Dr. Matthew Pusey, and Dr. Tobias Fritz.

The work on Blockcode is due to Wah Loon Keng.

Our work was sponsored by the Perimeter Institute Summer Student Research program.
