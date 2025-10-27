# incjet - LO single inclusive jet production cross-section calculation

Computes the leading-order cross-section of single inclusive jet production.

## Example run

A fetch script `fetch.sh` is provided to download and get the PDF needed for the calculation.
A compile script `compile.sh` is provided to create the executable.
Run the produced `incjet.exe` executable for results, which will also be output to `results.txt` file.

* Use 2->2 matrix element, and count both jets (inclusive).
* Differentiates between quark and gluon jet contributions.
* can be extended to hadronic final-states by including fragmentation functions.
* can be extended to photon/Z/W/Higgs-jet/hadron process.
* can be extended to heavy-ion collisions by including quenching effects and shadowing PDF.
* Since the CTEQ PDF wrapper is not thread safe, it can not be parallelized.
* One can replace the CTEQ PDF reader with LHAPDF, then it can be parallelized.
* Results can be compared with 2.76 and 5.02 *pp* data from ATLAS.
* A timer is included to display computation time.
* Code for plotting will be available soon.

For dijet observables, it gives trivial results and should not be used.
However, it can be extended to include higher order effects for dijet calculation.

### Compile and Run

```bash
./compile.sh
./incjet.exe
```

## References

* [J.F. Owens, *Large Momentum Transfer Production of Direct Photons, Jets, and Particles*, Rev.Mod.Phys. 59, 465 (1987)](https://doi.org/10.1103/RevModPhys.59.465)
* [Ellis, Stirling and Webber, *QCD and Collider Physics*, Camb.Monogr.Part.Phys.Nucl.Phys.Cosmol. 8 (1996) 1-435](https://doi.org/10.1017/CBO9780511628788)
