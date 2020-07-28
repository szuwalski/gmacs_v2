# ntheta
24
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
 0.18 0.01 1 -3 2 0.18 0.04
 7 -10 20 -1 0 -10 20
 9.111 -10 20 1 0 -10 20
 6.458 -10 20 2 0 -10 20
 72.5 65 130 -3 1 72.5 7.25
 0.75 0.3 1.6 3 0 0.1 5
 -0.1 -10 0.75 -2 0 -10 0.75
 0.75 0.2 1 -4 3 3 2
 0.001 0 1 -3 3 1.01 1.01
 0.6467 -10 5 2 0 10 20
 1.0034 -10 5 2 0 10 20
 1.3604 -10 5 2 0 10 20
 1.4042 -10 5 2 0 10 20
 1.4599 -10 5 2 0 10 20
 1.2657 -10 5 2 0 10 20
 0.7228 -10 5 2 0 10 20
 -100 -101 5 -2 0 10 20
 -100 -101 5 -2 0 10 20
 -100 -101 5 -2 0 10 20
 -100 -101 5 -2 0 10 20
 -100 -101 5 -2 0 10 20
 -100 -101 5 -2 0 10 20
 -100 -101 5 -2 0 10 20
 -100 -101 5 -2 0 10 20
# lw_type
2
# mean_wt_inv
 0.2229 0.3953 0.5153 0.8152 1.0714 1.3752 1.7169 2.011
# maturity
 0 0 0 1 1 1 1 1
# legal
 0 0 0 0 1 1 1 1
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
8
## Options for the growth increment model matrix
## 1: Linear
## 2: Individual
## 3: Individual (Same as 2)
# bUseGrowthIncrementModel
1
# bUseCustomMoltProbility
2
# nSizeClassRec
 3
# nSizeIncVaries
 1
# Start of the blocks in which molt increment changes (one row for each sex) - the first block starts in 1976
# Note: there is one less year than there are blocks
 # male
# nMoltVaries
 1
# Start of the blocks in which molt probability changes (one row for each sex) - the first block starts in 1976
# Note: there is one less year than there are blocks
 # male
# BetaParRelative
1
# Growth parameters
# Initial_value Lower_bound Upper_bound Phase Prior_type Prior_1 Prior_2
 11.5 5 20 3 0 0 20
 0.05 0 0.5 3 0 0 10
 0.75 0.2 3 3 0 0 3
 125 65 165 2 0 0 170
 0.07 0 1 2 0 0 3

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
#  Winter_Com Summer_Com ADFG_Trawl
 1 1 1 # selectivity periods
 0 0 0 # sex specific selectivity (1=Yes, 0=No)
 2 2 2 # selectivity type (by sex)
 0 0 0 # selectivity within another gear
 0 0 0 # extra parameters for each pattern
 1 1 1 # retention periods 
 0 0 0 # sex specific retention (1=Yes, 0=No)
 2 2 6 # retention type (by sex)
 1 1 0 # retention flag
 0 0 0 # extra parameters for each pattern

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
 1 1 1 0 110 40 200 0 10 200 2 1976 2019
 1 2 2 0 2 0.1 20 0 0.1 100 2 1976 2019
 2 3 1 0 90 30 200 0 10 200 2 1976 2019
 2 4 2 0 2.5 0.1 20 0 0.1 100 2 1976 2019
 3 5 1 0 85 30 200 0 10 200 3 1976 2019
 3 6 2 0 3 0.1 20 0 0.1 100 3 1976 2019
 -1 7 1 0 95 50 200 0 1 900 2 1976 2019
 -1 8 2 0 2.5 1 20 0 1 900 2 1976 2019
 -2 9 1 0 100 50 700 0 1 900 2 1976 2019
 -2 10 2 0 2 1 20 0 1 900 2 1976 2019
 -3 11 1 0 100 1 700 0 1 900 -3 1976 2019
#Number of asymptotic selectivity parameters
1
# Fleet Sex Year Initial lower_bound upper_bound phase
 1 1 1976 1e-006 0 1 -3
#Catchability
# Initial Lower_bound Upper_bound Phase Prior_type Prior_1 Prior_2 Index_lambda Index_lambda
 0.896 0.1 2 3 0 0.1 2 0 1 1
 1 0.1 2 -3 0 0.1 2 0 1 1
 0.0015 0 1 4 0 0 1 0 1 1
# Index CV
# Initial Lower_bound Upper_bound Phase Prior_type Prior_1 Prior_2
 0.0001 0 2 -4 4 1 100
 0.0001 0 2 -4 4 1 100
 0.0001 0 2 -4 4 1 100
# Controls on F
# Initial_male_f Initial_female_F Penalty_SD (early phase) Penalty_SD (later Phase) Phase_mean_F_male Phase_mean_F_female Lower_bound_mean_F Upper_bound_mean_F Lower_bound_annual_male_F Upper_bound_annual_male_F Lower_bound_annual_female_F Upper_bound_annual_female_F
 0.02 0 0.5 45.5 1 1 -12 4 -10 10 -10 10
 0.12 0 0.5 45.5 1 1 -12 4 -10 10 -10 10
 0 0 2 20 -1 -1 -12 4 -10 10 -10 10
# Options when fitting size-composition data
## Likelihood types: 
##  1:Multinomial with estimated/fixed sample size
##  2:Robust approximation to multinomial
##  3:logistic normal
##  4:multivariate-t
##  5:Dirichlet

#  Winter_Com Winter_Com Winter_Com Winter_Com Summer_Com Summer_Com Summer_Com Summer_Com Summer_Com Summer_Com ADFG_Trawl ADFG_Trawl ADFG_Trawl ADFG_Trawl
#  male male male male male male male male male male male male male male
#  retained retained total total retained retained discard discard total total total total total total
#  newshell oldshell newshell oldshell newshell oldshell newshell oldshell newshell oldshell newshell oldshell newshell oldshell
#  immature+mature immature+mature immature+mature immature+mature immature+mature immature+mature immature+mature immature+mature immature+mature immature+mature immature+mature immature+mature immature+mature immature+mature
 1 1 1 1 1 1 1 1 1 1 1 1 1 1 # Type of likelihood
 0 0 0 0 0 0 0 0 0 0 0 0 0 0 # Auto tail compression (pmin)
 1 1 1 1 1 1 1 1 1 1 1 1 1 1 # Initial value for effective sample size multiplier
 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 # Phz for estimating effective sample size (if appl.)
 1 1 2 2 3 3 4 4 5 5 6 6 7 7 # Composition appender
 1 1 1 1 1 1 1 1 1 1 1 1 1 1 # Lambda for effective sample size
 1 1 1 1 1 1 1 1 1 1 1 1 1 1 # Lambda for overall likelihood
# Type of M specification
## 1: Time-invariant M
## 2: Default random walk M
## 3: Cubic spline with time M
## 4: Blocked changes in  M
## 5: Blocked changes in  M (type 2)
## 6: Blocked changes in  M (returns to default)
# m_type
0
# Mdev_phz_def
3
# m_stdev
0.25
# m_nNodes_sex
 1
# Start of the blocks in which M changes (one row for each sex) - the first block starts in 1976
# Note: there is one less year than there are blocks
 1976 # male
# nSizeDevs
1
# Start of the size-class blocks in which M changes (one row for each sex) - the first block start at size-class 1
# Note: there is one less size-class than there are blocks (no input implies M is independent of size
 7
# Init_Mdev
1
# #Mparameters
 3 0.5 5 4 0
# maturity M
# Initial Lower_bound Upper_bound Phase Prior_type Prior_1 Prior_2
 0 -4 4 4 1 0 0.1

# Extra controls
1976 # First year of recruitment estimation
2019 # Last year of recruitment estimation
2 # Phase for recruitment estimation
-3 # Phase for recruitment sex-ratio estimation
0.5 # Initial value for recruitment sex-ratio
-3 # Phase for initial recruitment estimation
1 # VERBOSE FLAG (0 = off, 1 = on, 2 = objective func; 3 diagnostics)
3 # Initial conditions (0 = Unfished, 1 = Steady-state fished, 2 = Free parameters, 3 = Free parameters (revised))
1 # Lambda (proportion of mature male biomass for SPR reference points)
0 # Stock-Recruit-Relationship (0 = none, 1 = Beverton-Holt)
10 # Maximum phase (stop the estimation after this phase)
-1 # Maximum number of function calls

# catch_emphasis
 1 1 1
# Penalty_emphasis
 10000 0 1 2 0 0 10 10 0
# eof_ctl
9999
