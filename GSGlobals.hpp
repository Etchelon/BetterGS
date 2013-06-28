#ifndef _GSGLOBALS_HPP_GUARD
#define _GSGLOBALS_HPP_GUARD
/*
// NAME
//   GSP1.INC - Includes global indeces used throughout GS program
// SYNOPSIS
// FUNCTION
// VARIABLES
//   NCX       - int; maximum # of cycle components which can be handled
//   NCXT      - int; maximum # of components of the same type
//   NPX       - int; maximum # of points
//   NCVX      - int; maximum # of (convergence+parameter) variables
//   NCV$X     - int; maximum # of pure convergence variables, i.e. variables which
//               are required to converge to the value of the previous iter.
//               Their number sets the size of the eigenvalue problem
//   NIX,NOX   - int; maximum # of streams entering (exiting) each component
//               Must be NOX >= 4
//   NRIC      - int; # of rows of matrix IC. NRIC must be greatest between:
//                 a) 3+NIX+NOX+(Max # of component integer data)
//                 b) 3+NIX+NOX+(NIX-1)+(# of turbine integer data)
//   NISX,NOSX - int; maximum # of streams entering (exiting) the whole system
//   NTD       - int; # of rows of matrix TD describing component characteristics
//               Since vector ISK is used either to describe comp. char. and
//               convergence variables it must be 2*NTD > NCVX
//   NDX       - int; # of rows of matrix D
//               NOTICE: THIS DETERMINES IRL(3) AND OTHER VARIABLES IN GSBLOK
//   NEX       - int; maximum # of expansion steps in the turbine. IF CHANGED,
//               THIS PARAMETER MUST BE UPDATED ALSO IN SUBROUTINE GSTUR
//               Since NEX determines the size of a work matrix used also
//               by subroutine GSMIX, IT MUST BE:
//               ===>   14*(NEX+1) >= 20*(Max # of streams entering a mixer + 1)  <===
//               and:
//               ===>   14*(NEX+1) >= 29*5                                        <===
//   NEN       - int; maximum number of entropy losses category
//   NNX       - int; maximum number of entropy losses of a single component
//               (usuful to dimension matrix)
//   NPRX      - int; maximum number of priority levels
//   NSTMAX    - int; maximum number of turbine stages
//   ISTP      - int; maximum number of calculation steps for each row
//   NCTMAX    - int; maximum number of cooled turbine in the plant
//   NPTMAX    - int; maximum number of parameters regarding each stage of the cooled turbine
//   NSMAX  - maximum # of chemical species that can be handled
//   NAMAX  - maximum # of atoms that can be handled
//   NACB   - number of atoms to be oxidized in combustion processes. First
//   NAWW   - number of atoms which, during combustion, may form compounds
//            other than oxides (e.g. K forms K2CO3 instead of K2O)
//   NCMAX  - maximum # of characteristics of a thermodynamic point (T,P,v....)
//   NVMAX  - NCMAX+NSMAX+2 (the last 2 elements contain HHV and LHV)
// EXAMPLE
// NOTES
//   NTD increased from 78 to 80 by S. Consonni, Feb 6, 2003
//   NISX, NOSX increased from 18 to 25 by S. Consonni, Feb 10, 2003
// BUGS
//   NNX increased from 10 to 25 by S. Consonni, Apr 24, 2003
//   ATTENTION: this is due to an error in gss.for, where vector ITST
//   is dimensioned NNX but it is handled within loops with upper bound NIN
//   (see subroutine GSQWE). So when NIN > NNX program exceeds array bounds
//   THIS IS AN ERROR AND MUST BE FIXED!
// ERROR LOG
// SEE ALSO
//  ***
*/

#define NCX    104
#define NCXT   4
#define NPX    160
#define NCVPX  50
#define NCVX   30
#define NIX    7
#define NOX    10
#define NRIC   75
#define NISX   25
#define NOSX   25
#define NTD    80
#define NDX    125
#define NEX    50
#define NEN    15
#define NNX    25
#define NPRX   10
#define NGASX  2
#define NSTMAX 10
#define ISTP   60
#define NCTMAX 4
#define NPTMAX 110
#define NSMAX  36
#define NAMAX  36
#define NACB   7
#define NAWW   2
#define NCMAX  9
#define NVMAX  47

#endif