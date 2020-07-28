# ntheta
12
# Core parameters
## Initial: Initial value for the parameter (must lie between lower and upper)
## Lower & Upper: Range for the parameter
## Phase: Set equal to a negative number not to estimate
## Prior type:
## 0: Uniform   - parameters are the range of the uniform prior
## 1: Normal    - parameters are the mean and sd
## 2: Lognormal - parameters are the mean and sd of the log
## 3: Beta      - parameetrs are the two beta parameters [see dbeta]
## 4: Gamma     - parameetrs are the two gamma parameters [see dgamma]
# Initial_value Lower_bound Upper_bound Phase Prior_type Prior_1 Prior_2
 0.18 0.01 1 -4 2 0.18 0.02
 14.3 -7 30 -2 0 -7 30
 10 -7 20 -1 1 -10 20
 13.39 -7 20 1 0 -7 20
 80 30 310 -2 1 72.5 7.25
 0.25 0.1 7 -4 0 0.1 9
 0.2 -10 0.75 -4 0 -10 0.75
 0.75 0.2 1 -2 3 3 2
 0.01 0 1 -3 3 1.01 1.01
 14.5 5 20 1 0 5 20
 14 5 20 1 0 5 20
 13.5 5 20 1 0 5 20
# lw_type
3
# mean_wt_inv
 0.000748427 0.00116573 0.00193051
 0.000748427 0.00116573 0.00168889
 0.000748427 0.00116573 0.00192225
 0.000748427 0.00116573 0.00187796
 0.000748427 0.00116573 0.00193863
 0.000748427 0.00116573 0.00207641
 0.000748427 0.00116573 0.00189933
 0.000748427 0.00116573 0.00211669
 0.000748427 0.00116573 0.00193878
 0.000748427 0.00116573 0.00193976
 0.000748427 0.00116573 0.00187107
 0.000748427 0.00116573 0.0019983
 0.000748427 0.00116573 0.00187042
 0.000748427 0.00116573 0.00196941
 0.000748427 0.00116573 0.00192686
 0.000748427 0.00116573 0.00202149
 0.000748427 0.00116573 0.00193132
 0.000748427 0.00116573 0.00201441
 0.000748427 0.00116573 0.00197747
 0.000748427 0.00116573 0.00209925
 0.000748427 0.00116573 0.00198248
 0.000748427 0.00116573 0.00193093
 0.000748427 0.00116573 0.00193093
 0.000748427 0.00116573 0.00193093
 0.000748427 0.00116573 0.00193093
 0.000748427 0.00116573 0.00193093
 0.000748427 0.00116573 0.00193093
 0.000748427 0.00116573 0.00193093
 0.000748427 0.00116573 0.00193093
 0.000748427 0.00116573 0.00193093
 0.000748427 0.00116573 0.00193093
 0.000748427 0.00116573 0.00189163
 0.000748427 0.00116573 0.00179572
 0.000748427 0.00116573 0.00182311
 0.000748427 0.00116573 0.00180743
 0.000748427 0.00116573 0.00193093
 0.000748427 0.00116573 0.00189463
 0.000748427 0.00116573 0.00185061
 0.000748427 0.00116573 0.00193093
 0.000748427 0.00116573 0.00193093
 0.000748427 0.00116573 0.00193093
 0.000748427 0.00116573 0.00193093
# maturity
 0 1 1
# legal
 0 0 1
## Options for the growth matrix
## 1: Fixed growth transition matrix (requires molt probability)
## 2: Fixed size transition matrix (molt probability is ignored)
## 3: Growth increment is gamma distributed
## 4: Size after growth is gamma distributed
## 5: kappa varies among individuals
## 6: Linf varies among individuals
## 7: kappa and Ling varies among individuals
## 8: Growth increment is normally distributed
# bUseCustomGrowthMatrix
1
## Options for the growth increment model matrix
## 1: Linear
## 2: Individual
## 3: Individual (Same as 2)
# bUseGrowthIncrementModel
0
# bUseCustomMoltProbility
2
# nSizeClassRec
 1
# nSizeIncVaries
 1
# Start of the blocks in which molt increment changes (one row for each sex) - the first block starts in 1978
# Note: there is one less year than there are blocks
 # male
# nMoltVaries
 1
# Start of the blocks in which molt probability changes (one row for each sex) - the first block starts in 1978
# Note: there is one less year than there are blocks
 # male
# BetaParRelative
1
# Growth parameters
# Initial_value Lower_bound Upper_bound Phase Prior_type Prior_1 Prior_2
 121.5 65 145 -4 0 0 999
 0.06 0 1 -3 0 0 999
# trans(CustomGrowthMatrix(h,i))
 0.1761 0 0
 0.7052 0.2206 0
 0.1187 0.7794 1

## Selectivity parameter controls
## Selectivity (and retention) types
##   0: Nonparameric selectivity (one parameter per class)
##   1: Nonparameric selectivity (one parameter per class, constant from last specified class)
##   2: Logistic selectivity (inflection point and slope)
##   3: Logistic selectivity (50% and 95% selection)
##   4: Double normal selectivity (3 parameters)
##   5: Flat equal to zero (1 parameter; phase must be negative)
##   6: Flat equal to one (1 parameter; phase must be negative)
##   7: Flat-topped double normal selectivity (4 parameters)
##   8: Decling logistic selectivity with initial values (50% and 95% selection plus extra)
##   9: Cubic-spline (specified with knots and values at knots)
## Extra (type 1): number of selectivity parameters to estimated
#  Pot_Fishery Trawl_Bycatch Fixed_bycatch NMFS_Trawl ADFG_Pot
 2 1 1 1 1 # selectivity periods
 0 0 0 0 0 # sex specific selectivity (1=Yes, 0=No)
 0 3 3 0 0 # selectivity type (by sex)
 0 0 0 0 0 # selectivity within another gear
 0 0 0 0 0 # extra parameters for each pattern
 1 1 1 1 1 # retention periods 
 0 0 0 0 0 # sex specific retention (1=Yes, 0=No)
 3 6 6 6 6 # retention type (by sex)
 1 0 0 0 0 # retention flag
 0 0 0 0 0 # extra parameters for each pattern

# Selectvity parameters
## Fleet: The index of the fleet  (positive for capture selectivity; negative for retention)
## Index: Parameter count (not used)
## Paramter_no: Parameter count within the current pattern (not used)
## Sex: Sex (not used)
## Initial: Initial value for the parameter (must lie between lower and upper)
## Lower & Upper: Range for the parameter
## Phase: Set equal to a negative number not to estimate
## Prior type:
## 0: Uniform   - parameters are the range of the uniform prior
## 1: Normal    - parameters are the mean and sd
## 2: Lognormal - parameters are the mean and sd of the log
## 3: Beta      - parameters are the two beta parameters [see dbeta]
## 4: Gamma     - parameters are the two gamma parameters [see dgamma]
## Start / End block: years to define the current block structure
# Fleet Index Parameter_no Sex Initial Lower_bound Upper_bound Phase Prior_type Prior_1 Prior_2 Start_block End_block
 1 1 1 0 0.4 0.001 1 0 0 1 3 1978 2008
 1 2 2 0 0.7 0.001 1 0 0 1 3 1978 2008
 1 3 3 0 1 0.001 2 0 0 1 -2 1978 2008
 1 1 1 0 0.4 0.001 1 0 0 1 3 2009 2018
 1 2 2 0 0.4 0.001 1 0 0 1 3 2009 2018
 1 3 3 0 1 0.001 2 0 0 1 -2 2009 2018
 2 7 1 0 40 10 200 0 10 200 -3 1978 2018
 2 8 2 0 60 10 200 0 10 200 -3 1978 2018
 3 9 1 0 40 10 200 0 10 200 -3 1978 2018
 3 10 2 0 60 10 200 0 10 200 -3 1978 2018
 4 11 1 0 0.7 0.001 1 0 0 1 4 1978 2019
 4 12 2 0 0.8 0.001 1 0 0 1 4 1978 2019
 4 13 3 0 0.9 0.001 1 0 0 1 -5 1978 2019
 5 14 1 0 0.4 0.001 1 0 0 1 4 1978 2019
 5 15 2 0 0.7 0.001 1 0 0 1 4 1978 2019
 5 16 3 0 1 0.001 2 0 0 1 -2 1978 2019
 -1 17 1 0 120 50 200 0 1 900 -7 1978 2018
 -1 18 2 0 123 110 200 0 1 900 -7 1978 2018
 -2 19 1 0 595 1 999 0 1 999 -3 1978 2018
 -3 20 1 0 595 1 999 0 1 999 -3 1978 2018
 -4 21 1 0 595 1 999 0 1 999 -3 1978 2019
 -5 22 1 0 595 1 999 0 1 999 -3 1978 2019
#Number of asymptotic selectivity parameters
1
# Fleet Sex Year Initial lower_bound upper_bound phase
 1 1 1978 1e-006 0 1 -3
#Catchability
# Initial Lower_bound Upper_bound Phase Prior_type Prior_1 Prior_2 Index_lambda Index_lambda
 1 0.5 1.2 -4 0 0 9 0 1 1
 0.003 0 5 3 0 0 9 0 1 1
# Index CV
# Initial Lower_bound Upper_bound Phase Prior_type Prior_1 Prior_2
 1e-007 1e-008 10 -4 4 1 100
 1e-007 1e-008 10 -4 4 1 100
# Controls on F
# Initial_male_f Initial_female_F Penalty_SD (early phase) Penalty_SD (later Phase) Phase_mean_F_male Phase_mean_F_female Lower_bound_mean_F Upper_bound_mean_F Lower_bound_annual_male_F Upper_bound_annual_male_F Lower_bound_annual_female_F Upper_bound_annual_female_F
 0.2 0 3 50 1 -1 -12 4 -10 10 -10 10
 0.0001 0 4 50 1 -1 -12 4 -10 10 -10 10
 0.0001 0 4 50 1 -1 -12 4 -10 10 -10 10
 0 0 2 20 -1 -1 -12 4 -10 10 -10 10
 0 0 2 20 -1 -1 -12 4 -10 10 -10 10
# Options when fitting size-composition data
## Likelihood types: 
##  1:Multinomial with estimated/fixed sample size
##  2:Robust approximation to multinomial
##  3:logistic normal
##  4:multivariate-t
##  5:Dirichlet

#  Pot_Fishery NMFS_Trawl ADFG_Pot
#  male male male
#  total total total
#  all_shell all_shell all_shell
#  immature+mature immature+mature immature+mature
 2 2 2 # Type of likelihood
 0 0 0 # Auto tail compression (pmin)
 1 1 1 # Initial value for effective sample size multiplier
 -4 -4 -4 # Phz for estimating effective sample size (if appl.)
 1 2 3 # Composition appender
 1 1 1 # Lambda for effective sample size
 1 1 1 # Lambda for overall likelihood
# Type of M specification
## 1: Time-invariant M
## 2: Default random walk M
## 3: Cubic spline with time M
## 4: Blocked changes in  M
## 5: Blocked changes in  M (type 2)
## 6: Blocked changes in  M (returns to default)
# m_type
6
# Mdev_phz_def
3
# m_stdev
10
# m_nNodes_sex
 2
# Start of the blocks in which M changes (one row for each sex) - the first block starts in 1978
# Note: there is one less year than there are blocks
 1998 1999 # male
# nSizeDevs
0
# Start of the size-class blocks in which M changes (one row for each sex) - the first block start at size-class 1
# Note: there is one less size-class than there are blocks (no input implies M is independent of size

# Init_Mdev
1
# #Mparameters
 1.6 0 2 3 0
# #Mparameters
 0 -2 2 -99 0
# maturity M
# Initial Lower_bound Upper_bound Phase Prior_type Prior_1 Prior_2
 0 -4 4 4 1 0 0.1

# Extra controls
1978 # First year of recruitment estimation
2018 # Last year of recruitment estimation
3 # Phase for recruitment estimation
-3 # Phase for recruitment sex-ratio estimation
0.5 # Initial value for recruitment sex-ratio
-3 # Phase for initial recruitment estimation
0 # VERBOSE FLAG (0 = off, 1 = on, 2 = objective func; 3 diagnostics)
2 # Initial conditions (0 = Unfished, 1 = Steady-state fished, 2 = Free parameters, 3 = Free parameters (revised))
1 # Lambda (proportion of mature male biomass for SPR reference points)
0 # Stock-Recruit-Relationship (0 = none, 1 = Beverton-Holt)
10 # Maximum phase (stop the estimation after this phase)
-1 # Maximum number of function calls

# catch_emphasis
 1 1 1 1
# Penalty_emphasis
 10000 1 1 1 0 0 1 10 0
# eof_ctl
9999
