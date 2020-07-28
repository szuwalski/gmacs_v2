#
#  ===========================================  #
#  Controls  for  leading  parameter  vector  theta
#  LEGEND  FOR  PRIOR:
#  0 = uniform, 1 = normal, 2 = lognormal, 3 =  beta, 4 =  gamma
#  ===========================================  #
#  ntheta
24
# =========================================== #
# ival        lb        ub        phz   prior     p1      p2         # parameter         #
# =========================================== #
  0.18      0.01         1         -3       2   0.18    0.04         # M
  7.0        -10        20         -1       0   -10       20         # logR0
  9.111      -10        20          1       0   -10       20         # logRini, to estimate if NOT initialized at unfished
  6.458      -10        20          2       0   -10       20         # logRbar, to estimate if NOT initialized at unfished
  72.5        65       130         -3       1   72.5    7.25         # recruitment expected value (males or combined)
  0.75       0.3       1.6          3       0    0.1       5         # recruitment scale (variance component) (males or combined)
 -0.10       -10      0.75         -2       0    -10    0.75         # ln(sigma_R)
  0.75      0.20      1.00         -4       3    3.0    2.00         # steepness
  0.001     0.00      1.00         -3       3    1.01   1.01         # recruitment autocorrelation
#  0.00     -10         4          2        0   10.0    20.00        # Deviation for size-class 1 (normalization class)
 0.6467     -10         5          2        0   10.0    20.00        # Deviation for size-class 2
 1.0034     -10         5          2        0   10.0    20.00        # Deviation for size-class 3
 1.3604     -10         5          2        0   10.0    20.00        # Deviation for size-class 4
 1.4042     -10         5          2        0   10.0    20.00        # Deviation for size-class 5
 1.4599     -10         5          2        0   10.0    20.00        # Deviation for size-class 6
 1.2657     -10         5          2        0   10.0    20.00        # Deviation for size-class 7
 0.7228     -10         5          2        0   10.0    20.00        # Deviation for size-class 8
 -100.00    -101        5         -2        0   10.0    20.00        # Deviation for size-class 1  (oldshell)
 -100.00    -101        5         -2        0   10.0    20.00        # Deviation for size-class 2
 -100.00    -101        5         -2        0   10.0    20.00        # Deviation for size-class 3
 -100.00    -101        5         -2        0   10.0    20.00        # Deviation for size-class 4
 -100.00    -101        5         -2        0   10.0    20.00        # Deviation for size-class 5
 -100.00    -101        5         -2        0   10.0    20.00        # Deviation for size-class 6
 -100.00    -101        5         -2        0   10.0    20.00        # Deviation for size-class 7
 -100.00    -101        5         -2        0   10.0    20.00        # Deviation for size-class 8


# weight-at-length input  method  (1 = allometry  [w_l = a*l^b],  2 = vector by sex)
 2
# Male weight-at-length
# 0.49140719 0.87146954 1.1361117 1.7971926 2.3619521 3.0318207 3.7850237 4.4334877   #lbs
 0.2229  0.3953  0.5153  0.8152  1.0714  1.3752  1.7169  2.0110                       #kg
# Proportion mature by sex
 0       0       0      1       1       1       1       1
# Proportion legal by sex
 0       0       0       0       1       1       1      1

## ========================================== ##
## GROWTH PARAM CONTROLS                                                                ##
##     Two lines for each parameter if split sex, one line if not                       ##
## ========================================== ##
# Use growth transition matrix option (1=read in growth-increment matrix; 2=read in size-transition; 3=gamma distribution for size-increment; 4=gamma distribution for size after increment)
8
# growth increment model (1=alpha/beta; 2=estimated by size-class;3=pre-specified/emprical)
1
# molt probability function (0=pre-specified; 1=flat;2=declining logistic)
2
# maximum size-class (males then females)
#8
# Maximum size-class for recruitment(males then females)
3
## number of size-increment periods
1
## Year(s) size-incremnt period changes (blank if no changes)

## number of molt periods
1
## Year(s) molt period changes (blank if no changes)

## Beta parameters are relative (1=Yes;0=no)
1

## ========================================== ##
# ival        lb        ub        phz   prior     p1      p2         # parameter         #
# =========================================== #
  11.5       5.0      20.0          3       0    0.0    20.0         # alpha males or combined
  0.05       0.0       0.5          3       0    0.0    10.0         # beta males or combined
   0.75      0.20      3.0          3       0    0.0     3.0         # gscale males or combined
  125.0      65.0     165.0         2       0    0.0   170.0         # molt_mu males or combined
   0.07      0.0       1.0          2       0    0.0     3.0         # molt_cv males or combined
# ========================================== ##
# The custom growth-increment matrix

# custom molt probability matrix

##  ==========================================  ##
## SELECTIVITY CONTROLS                                                                   ##
##     Selectivity P(capture of all sizes). Each gear must have a selectivity and a       ##
##     retention selectivity. If a uniform prior is selected for a parameter then the     ##
##     lb and ub are used (p1 and p2 are ignored)                                         ##
## LEGEND                                                                                 ##
##     sel type: 0 = parametric (nclass), 1 = indiviudal parameter for each class(nclass),##
##               2 = logistic (2), 3 = logistic95 (2), 4 = double normal (3),             ##
##               5 = uniform=1 (1), 6 = uniform=0 (1)                                     ##
##     gear index: use +ve for selectivity, -ve for retention                             ##
##     sex dep: 0 for sex-independent, 1 for sex-dependent                                ##
##  ==========================================  ##
##  ivector  for  number  of  year  blocks  or  nodes  ##
## Gear-1   Gear-2   Gear-3   Gear-4   Gear-5
## WinCom Winsub  Sumpot     ADFG     NMFS
## WinCom  Sumpot  ADFG     NMFS
   1         1        1     #   1         # selectivity periods
   0         0        0     #   0         # sex specific selectivity
   2         2        2     #   2         # male selectivity type
   0         0        0     #   0         # within another gear
   0 		 0 		  0 	#   0 		  # extra parameters   
## Gear-1    Gear-2   Gear-3   Gear-4
   1         1        1     #   1         # retention periods
   0         0        0     #   0         # sex specific retention
   2         2        6     #   6         # male   retention type
   1         1        0     #   0         # male   retention flag (0 = no, 1 = yes)
   0 		 0 		  0 	#   0 		  # extra parameters
   1		 1		  1 	#   1 		  # selectivity forced to max at 1? (1=yes; 0=no)
##  ==========================================##
##  Selectivity  P(capture  of  all  sizes)
## ========================================== ##
## gear  par   sel                                             phz    start  end        ##
## index index par sex  ival  lb    ub     prior p1     p2     mirror period period     ##
## ========================================== ##
## Gear-1
#   1     1     1   0    0.10   0.0  0.9    0      0.0   1.0    2     1976   2019
#   1     2     2   0    0.15   0.0  0.9    0      0.0   1.0    2     1976   2019
#   1     3     3   0    0.20   0.0  0.9    0      0.0   1.0    2     1976   2019
#   1     4     4   0    0.25   0.0  0.9    0      0.0   1.0    2     1976   2019
#   1     5     5   0    0.20   0.0  0.9    0      0.0   1.0    2     1976   2019
#   1     6     6   0    0.15   0.0  0.9    0      0.0   1.0    2     1976   2019
#   1     7     7   0    0.10   0.0  0.9    0      0.0   1.0    2     1976   2019
#   1     8     8   0    0.08   0.0  0.9    0      0.0   1.0    2     1976   2019
## Gear-2
#   2     9     1   0     90    30   200    0      10    200    2     1976   2019
#   2     10    2   0    2.5    0.1   20    0      0.1   200    2     1976   2019
## Gear-3
#   3     11    1   0     85    30   200    0      10    200    3     1976   2019
#   3     12    2   0    3.0   0.1    20    0      0.1   200    3     1976   2019
## Gear-4
##   4     13    1   0     85    30   200    0      10    200    3     1976   2019
##   4     14    2   0    3.0    0.1   20    0      0.1   200    3     1976   2019
### ========================================== ##
### Retained
### gear  par   sel                                             phz    start  end        ##
### index index par sex  ival  lb    ub     prior p1     p2     mirror period period     ##
## Gear-1
#  -1     13    1   0     95   50    200    0      1    900    2     1976   2019
#  -1     14    2   0    2.5   1.0    20    0      1    900    2     1976   2019
## Gear-2
#  -2     15    1   0    100    50   700    0      1    900    2     1976   2019
#  -2     16    2   0    2.0   1.0    20    0      1    900    2     1976   2019
## Gear-3
#  -3     17    1   0    100    1    700    0      1    900   -3     1976   2019
## Gear-4
#  -4     20    1   0    100    1    700    0      1    900   -3     1976   2019
## ========================================== ##

## gear  par   sel                                             phz    start  end        ##
## index index par sex  ival  lb    ub     prior p1     p2     mirror period period     ##
## ========================================== ##
# Gear-1
   1     1     1   0     110    40  200    0       10   200    2     1976   2019
   1     2     2   0     2.0   0.1   20    0      0.1   100    2     1976   2019
# Gear-2
   2     3     1   0     90    30   200    0      10    200    2     1976   2019
   2     4     2   0    2.5    0.1   20    0      0.1   100    2     1976   2019
# Gear-3
   3     5     1   0     85    30   200    0      10    200    3     1976   2019
   3     6     2   0    3.0   0.1    20    0      0.1   100    3     1976   2019
## Gear-4
#   4     7     1   0     85    30   200    0      10    200    3     1976   2019
#   4     8     2   0    3.0    0.1   20    0      0.1   100    3     1976   2019
## ========================================== ##
## Retained
## gear  par   sel                                             phz    start  end        ##
## index index par sex  ival  lb    ub     prior p1     p2     mirror period period     ##
# Gear-1
  -1      7    1   0     95   50    200    0      1    900    2     1976   2019
  -1      8    2   0    2.5   1.0    20    0      1    900    2     1976   2019
# Gear-2
  -2      9    1   0    100    50   700    0      1    900    2     1976   2019
  -2     10    2   0    2.0   1.0    20    0      1    900    2     1976   2019
# Gear-3
  -3     11    1   0    100    1    700    0      1    900   -3     1976   2019
## Gear-4
#  -4     14    1   0    100    1    700    0      1    900   -3     1976   2019
## ========================================== ##
# Number of asyptotic parameters
1
# Fleet   Sex     Year       ival   lb   ub    phz
       1     1     1976   0.000001   0    1     -3
## ========================================== ##
## PRIORS FOR CATCHABILITY
##     If a uniform prior is selected for a parameter then the lb and ub are used (p1   ##
##     and p2 are ignored). ival must be > 0                                            ##
## LEGEND                                                                               ##
##     prior: 0 = uniform, 1 = normal, 2 = lognormal, 3 = beta, 4 = gamma               ##
## ========================================== ##
## SURVEYS/INDICES ONLY
## ADFG:NMFS:STCPUE
## ival     lb       ub    phz   prior  p1        p2     Analytic?   LAMBDA   Emphasis
   0.896     0.1      2     3    0      0.1      2.0     0           1             1
   1         0.1      2     -3    0      0.1      2.0     0           1             1
   0.0015    0.0      1     4    0      0.0      1.00    0           1             1
##  ==========================================##
## ADDITIONAL CV FOR SURVEYS/INDICES
##     If a uniform prior is selected for a parameter then the lb and ub are used (p1   ##
##     and p2 are ignored). ival must be > 0                                            ##
## LEGEND                                                                               ##
##     prior type: 0 = uniform, 1 = normal, 2 = lognormal, 3 = beta, 4 = gamma          ##
## ========================================== ##
## ival        lb        ub        phz   prior     p1      p2
   0.0001      0.0       2.0      -4     4         1.0     100   # ADFG
   0.0001      0.0       2.0      -4     4         1.0     100   # NMFS
   0.0001      0.0       2.0      -4     4         1.0     100   # CPUE
## ========================================== ##
##  ==========================================##
##  PENALTIES  FOR  AVERAGE  FISHING  MORTALITY  RATE  FOR  EACH  GEAR
##  ==========================================##
##  Trap  Trawl  NMFS  BSFRF
## Mean_F   Fema-Offset STD_PHZ1 STD_PHZ2 PHZ_M PHZ_F   Lb    Ub     Lb     Ub      Lb     Ub
   0.02        0.0         0.5    45.50    1     1     -12      4    -10     10     -10    10   # WPot
   0.12        0.0         0.5    45.50    1     1     -12      4    -10     10     -10    10   # Spot
   0.00        0.0         2.00   20.00   -1    -1     -12      4    -10     10     -10    10   # ADFG survey (0 catch)
#  0.00        0.0         2.00   20.00   -1    -1     -12      4    -10     10     -10    10   # NMFS survey (0 catch)
##  ==========================================##
## OPTIONS FOR SIZE COMPOSTION DATA                                                     ##
##     One column for each data matrix                                                  ##
## LEGEND                                                                               ##
##     Likelihood: 1 = Multinomial with estimated/fixed sample size                     ##
##                 2 = Robust approximation to multinomial                              ##
##                 3 = logistic normal (NIY)                                            ##
##                 4 = multivariate-t (NIY)                                             ##
##                 5 = Dirichlet                                                        ##
## AUTO TAIL COMPRESSION                                                                ##
##     pmin is the cumulative proportion used in tail compression                       ##
##  =========================================  ##
#  Wcom    Wsur    Scom    Sdisc   Stot    ADFG    NMFS
   1   1   1   1   1   1   1   1   1   1   1   1   1   1   # Type of likelihood
   0   0   0   0   0   0   0   0   0   0   0   0   0   0   # Auto tail compression (pmin)
   1   1   1   1   1   1   1   1   1   1   1   1   1   1   # Initial value for effective sample size multiplier
  -4  -4  -4  -4  -4  -4  -4  -4  -4  -4  -4  -4  -4  -4   # Phz for estimating effective sample size (if appl.)
   1   1   2   2   3   3   4   4   5   5   6   6   7   7   # Composition aggregator
   1   1   1   1   1   1   1   1   1   1   1   1   1   1   # LAMBDA
   1   1   1   1   1   1   1   1   1   1   1   1   1   1   # Emphasis AEP
##  =========================================  ##
##  TIME  VARYING  NATURAL  MORTALIIY  RATES  ##
##  =========================================E##
## Type: 0 = constant natural mortality                                                 ##
##       1 = Random walk (deviates constrained by variance in M)                        ##
##       2 = Cubic Spline (deviates constrained by nodes & node-placement)              ##
##       3 = Blocked changes (deviates constrained by variance at specific knots)       ##
##       4 = Changes in pre-specified blocks                                            ##
##       5 = Changes in some knots                                                      ##
##       6 = Changes in Time blocks                                                     ##
  0
## M is relative (YES=1; NO=0)

## Phase of estimation
 3
## STDEV in m_dev for Random walk
 0.25
## Number of nodes for cubic spline or number of step-changes for option 3
 1
## Year position of the knots (vector must be equal to the number of nodes)
 1976
## number of breakpoints in M by size
 1
# line groups for breakpoint
 7
## Specific initial values for the natural mortality devs (0-no, 1=yes)
 1
## ival        lb        ub        phz    extra
    3.0        0.5       5.0       4        0
	
##========================================================================================
# maturity specific natural mortality? (yes = 1; no = 0; only for use if nmature > 1)
0	
## ??????????????????????????????????????????????????????????????????????????????????????????? ##																					
## ival        lb        ub        phz      prior     p1      p2         # parameter     ##																					
## ??????????????????????????????????????????????????????????????????????????????????????????? ##																					
 0.000000      -4          4        4      	1 		0 		0.1	# offset for immature male natural mortality																		
## ==================================================================================== ##

##  ========================================== ##
##  OTHER  CONTROLS
##  ========================================== ##
1976       # First rec_dev
2019       # last rec_dev
   2       # Estimated rec_dev phase
  -3       # Estimated sex_ratio
 0.5       # initial sex-ratio  
  -3       # Estimated rec_ini phase
   1       # VERBOSE FLAG (0 = off, 1 = on, 2 = objective func; 3 diagnostics)
   3       # Initial conditions (0 = Unfished, 1 = Steady-state fished, 2 = Free parameters, 3 = Free parameters (revised))
   1       # Lambda (proportion of mature male biomass for SPR reference points).
   0       # Stock-Recruit-Relationship (0 = none, 1 = Beverton-Holt)
   10       # Maximum phase (stop the estimation after this phase).
   -1       # Maximum number of function calls
## EMPHASIS FACTORS (CATCH)
#Wret_male  Wtot_male    Sret-male
        1         1           1

## EMPHASIS FACTORS (Priors)
# Log_fdevs   meanF       Mdevs  Rec_devs Initial_devs Fst_dif_dev Mean_sex-Ratio  Molt_prob	Free_sel
    10000       0        1.0         2            0           0             10      10    		0         
##  EOF
9999

