# rational-1d-2d-bijection
Arithmetic and visualization code for bijectively mapping between all rational numbers and all rational coordinates on the cartesian plane. Also known as space filling curve, though isn't continuous or local, and is instead infinite resolution.

The arithmetic and visualizaiton softwares are separate. The former (FP) produces a map (iterationFile) for indexing between positive rational numbers and rational coordinates on the cartesian plane. The latter (2d_1d_Python_Demo) takes that map and, depending on what maxL is set to in the code, visualizes the map for demonstration purposes. The latter software is slower and was really only used to produce the "WATCHME" gif. The true gem is rationaliterator.cpp.

That being said, software based on cantor pairing would have much more easily acheived what this software achieves, and perhaps more reliably as well. The arithmetic code is also evidently incomplete, you'll notice, as the early framework for a user give-and-receive prompt system and a visualization process is included in parts of the code. FP was also produces as a final project for a class, which will be apparent as well.
