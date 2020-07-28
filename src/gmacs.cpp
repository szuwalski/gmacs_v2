#ifdef DEBUG
  #ifndef __SUNPRO_C
    #include <cfenv>
    #include <cstdlib>
  #endif
#endif
  /**
   * @file gmacs.cpp
   * @authors Steve Martell, Jim Ianelli, D'Arcy Webber
  **/
  #include <admodel.h>
  #include <time.h>
  adstring like_names;
  adstring prior_names;
  #if defined __APPLE__ || defined __linux
  #include "./include/libgmacs.h"
  #endif
  #if defined _WIN32 || defined _WIN64
  #include "include\libgmacs.h"
  #endif
  time_t start,finish;
  long hour,minute,second;
  double elapsed_time;
  ofstream OutFile1;
  ofstream OutFile2;
  ofstream OutFile3;
  // Define objects for report file, echoinput, etc.
  /**
  \def report(object)
  Prints name and value of \a object on ADMB report %ofstream file.
  */
  #undef REPORT
  #define REPORT(object) OutFile1 << #object "\n" << setw(8) \
  << setprecision(4) << setfixed() << object << endl; \
  OutFile2 << #object "\n" << setw(8) \
  << setprecision(4) << setfixed() << object << endl;
  /**
   * \def COUT(object)
   * Prints object to screen during runtime.
   * cout <<setw(6) << setprecision(3) << setfixed() << x << endl;
  **/
  #undef COUT
  #define COUT(object) cout << #object "\n" << setw(6) \
   << setprecision(6) << setfixed() << object << endl;
  #undef MAXIT
  #undef TOL
  #define MAXIT 100
  #define TOL 1.0e-4
  /**
  \def MCout(object)
  Prints name and value of \a object on echoinput %ofstream file.
  */
  #undef MCout
  #define MCout(object) mcout << #object << " " << object << endl;
  /**
  \def ECHO(object)
  Prints name and value of \a object on echoinput %ofstream file.
  */
  #undef ECHO
  #define ECHO(object) echoinput << #object << "\n" << object << endl;
  /**
  \def WriteFileName(object)
  Prints name and value of \a object on control %ofstream file.
  */
  #undef WriteFileName
  #define WriteFileName(object) ECHO(object); gmacs_files << "# " << #object << "\n" << object << endl;
  /**
  \def WriteCtl(object)
  Prints name and value of \a object on control %ofstream file.
  */
  #undef WriteCtl
  #define WriteCtl(object) ECHO(object); gmacs_ctl << "# " << #object << "\n" << object << endl;
  /**
  \def WRITEDAT(object)
  Prints name and value of \a object on data %ofstream file.
  */
  #undef WRITEDAT
  #define WRITEDAT(object) ECHO(object); gmacs_data << "# " << #object << "\n" << object << endl;
  /**
  \def WRITEPRJ(object)
  Prints name and value of \a object on projecton %ofstream file.
  */
  #undef WRITEPRJ
  #define WRITEPRJ(object) ECHO(object); gmacs_prj << "# " << #object << "\n" << object << endl;
  /**
  Define a bunch of constants
  */
  //#undef TINY
  //#define TINY 1.0e-10
  #undef YES
  #define YES 1
  #undef NO
  #define NO 0
  #undef INSTANT_F
  #define INSTANT_F 0
  #undef CONTINUOUS_F
  #define CONTINUOUS_F 1
  #undef NOGROWTH_DATA
  #define NOGROWTH_DATA 0
  #undef GROWTHINC_DATA
  #define GROWTHINC_DATA 1
  #undef GROWTHCLASS_DATA
  #define GROWTHCLASS_DATA 2
  #undef NO_CUSTOM_M
  #define NO_CUSTOM_M 0
  #undef WITH_CUSTOM_M
  #define WITH_CUSTOM_M 1
  #undef LW_RELATIONSHIP
  #define LW_RELATIONSHIP 1
  #undef LW_VECTOR
  #define LW_VECTOR 2
  #undef LW_MATRIX
  #define LW_MATRIX 3
  #undef MALESANDCOMBINED
  #define MALESANDCOMBINED 1
  #undef FEMALES
  #define FEMALES 2
  #undef BOTHSEX
  #define BOTHSEX 0
  #undef UNDET_SHELL
  #define UNDET_SHELL 0
  #undef NEW_SHELL
  #define NEW_SHELL 1
  #undef OLD_SHELL
  #define OLD_SHELL 2
  
  #undef IMMATURE
  #define IMMATURE 2
  #undef MATURE
  #define MATURE 1
  #undef BOTHMATURE
  #define BOTHMATURE 0
  #undef TOTALCATCH
  #define TOTALCATCH 0
  #undef RETAINED
  #define RETAINED 1
  #undef DISCARDED
  #define DISCARDED 2
  #undef UNFISHEDEQN
  #define UNFISHEDEQN 0
  #undef FISHEDEQN
  #define FISHEDEQN 1
  #undef FREEPARS
  #define FREEPARS 2
  #undef FREEPARSSCALED
  #define FREEPARSSCALED 3
  #undef REFPOINTS
  #define REFPOINTS 4
  #undef SELEX_PARAMETRIC
  #define SELEX_PARAMETRIC 0
  #undef SELEX_COEFFICIENTS
  #define SELEX_COEFFICIENTS 1
  #undef SELEX_STANLOGISTIC
  #define SELEX_STANLOGISTIC 2
  #undef SELEX_5095LOGISTIC
  #define SELEX_5095LOGISTIC 3
  #undef SELEX_DOUBLENORM
  #define SELEX_DOUBLENORM 4
  #undef SELEX_UNIFORM1
  #define SELEX_UNIFORM1 5
  #undef SELEX_UNIFORM0
  #define SELEX_UNIFORM0 6
  #undef SELEX_DOUBLENORM4
  #define SELEX_DOUBLENORM4 7
  #undef SELEX_DECLLOGISTIC
  #define SELEX_DECLLOGISTIC 8
  #undef SELEX_CUBIC_SPLINE
  #define SELEX_CUBIC_SPLINE 9
  #undef GROWTH_FIXEDGROWTHTRANS
  #define GROWTH_FIXEDGROWTHTRANS 1
  #undef GROWTH_FIXEDSIZETRANS
  #define GROWTH_FIXEDSIZETRANS 2
  #undef GROWTH_INCGAMMA
  #define GROWTH_INCGAMMA 3
  #undef GROWTH_SIZEGAMMA
  #define GROWTH_SIZEGAMMA 4
  #undef GROWTH_VARYK
  #define GROWTH_VARYK 5
  #undef GROWTH_VARYLINF
  #define GROWTH_VARYLINF 6
  #undef GROWTH_VARYKLINF
  #define GROWTH_VARYKLINF 7
  #undef GROWTH_NORMAL
  #define GROWTH_NORMAL 8
  #undef FIXED_PROB_MOLT
  #define FIXED_PROB_MOLT 0
  #undef CONSTANT_PROB_MOLT
  #define CONSTANT_PROB_MOLT 1
  #undef LOGISTIC_PROB_MOLT
  #define LOGISTIC_PROB_MOLT 2
  #undef FREE_PROB_MOLT
  #define FREE_PROB_MOLT 3
  #undef UNIFORM_PRIOR
  #define UNIFORM_PRIOR 0
  #undef NORMAL_PRIOR
  #define NORMAL_PRIOR 1
  #undef LOGNORMAL_PRIOR
  #define LOGNORMAL_PRIOR 2
  #undef BETA_PRIOR
  #define BETA_PRIOR 3
  #undef GAMMA_PRIOR
  #define GAMMA_PRIOR 4
  #undef LINEAR_GROWTHMODEL
  #define LINEAR_GROWTHMODEL 1
  #undef INDIVIDUAL_GROWTHMODEL1
  #define INDIVIDUAL_GROWTHMODEL1 2
  #undef INDIVIDUAL_GROWTHMODEL2
  #define INDIVIDUAL_GROWTHMODEL2 3
  #undef M_CONSTANT
  #define M_CONSTANT 0
  #undef M_RANDOM
  #define M_RANDOM 1
  #undef M_CUBIC_SPLINE
  #define M_CUBIC_SPLINE 2
  #undef M_BLOCKED_CHANGES
  #define M_BLOCKED_CHANGES 3
  #undef M_TIME_BLOCKS1
  #define M_TIME_BLOCKS1 4
  #undef M_TIME_BLOCKS3
  #define M_TIME_BLOCKS3 5
  #undef M_TIME_BLOCKS2
  #define M_TIME_BLOCKS2 6
  #undef NOPROJECT
  #define NOPROJECT 0
  #undef PROJECT
  #define PROJECT 1
  #undef UNIFORMSR
  #define UNIFORMSR 1
  #undef RICKER
  #define RICKER 2
  #undef BEVHOLT
  #define BEVHOLT 3
  #undef MEAN_RECRUIT
  #define MEAN_RECRUIT 4
  
  #undef CONSTANTREC
  #define CONSTANTREC 0
  #undef STOCKRECREC
  #define STOCKRECREC 1
  adstring anystring;
  adstring_array fleetname;
  adstring_array sexes;
  // Open output files using ofstream
  // This one for easy reading all input to R
  ofstream mcout("mcout.rep");
  ofstream mcoutSSB("mcoutSSB.rep");
  ofstream mcoutREC("mcoutREC.rep");
  ofstream mcoutREF("mcoutREF.rep");
  ofstream mcoutPROJ("mcoutPROJ.rep");
  ofstream echoinput("checkfile.rep");
  // These ones for compatibility with ADMB (# comment included)
  ofstream gmacs_files("gmacs_files_in.dat");
  ofstream gmacs_data("gmacs_in.dat");
  ofstream gmacs_ctl("gmacs_in.ctl");
  ofstream gmacs_prj("gmacs_in.prj");
  // Specify random number generation
  random_number_generator rng(666);
  
  // pointer to array of pointers for selectivity functions
  class gsm::Selex<dvar_vector>** ppSLX = 0;//initialized to NULL
 double GenJitter(int JitterType, double Initial, double lower, double upper, int Phase, double sdJitter, dvector& rands, dvector& randu)
  {
   RETURN_ARRAYS_INCREMENT();
   double ParValue,eps;
   ParValue = Initial;
   if (Phase > 0)
    {
   
     // Andre's version
     if (JitterType==1)
      {
       int ifound = 0;
       ParValue = Initial;
       int ii = 1;
       if (Phase > 0)
        while (ifound ==0)
         {
          eps = rands(ii);
          ii += 1;
          if (eps > 0)
           ParValue = Initial + eps*(upper-Initial)*sdJitter/4.0;
          else
           ParValue = Initial + eps*(Initial-lower)*sdJitter/4.0;
          if (ParValue > lower & ParValue < upper) ifound = 1;
         } 
      }   
     // Buck's version
     if (JitterType==2)
      {
       double d = upper - lower;
       lower = lower+0.001*d;                        //shrink lower bound
       upper = upper-0.001*d;                        //shrink upper bound
       d = upper - lower;                            //shrink interval
       double lp = Initial - 0.5*d*sdJitter;
       double up = Initial + 0.5*d*sdJitter;
       double rp = Initial + (randu(1)-0.5)*d*sdJitter;
       if (rp > upper)      
        {rp = lp - (rp-upper);}
       else 
         if (rp < lower) {rp = up + (lower-rp);}
       ParValue = rp;  
      } 
     // Jie's version
     if (JitterType==3)
      {
       double tem1 = 0.5*rands(1)*sdJitter*log( (upper-lower+0.0000003)/(Initial-lower+0.0000001)-1.0);
       ParValue = lower+(upper-lower)/(1.0+exp(-2.0*tem1));
      }
    }  
      
      
   
   RETURN_ARRAYS_DECREMENT();
   return (ParValue);
  } 
 double CheckBounds(const prevariable& xx, double lower, double upper)
  {
   RETURN_ARRAYS_INCREMENT();
   int Status;
   double Range;
   Status = 0;
   Range = upper - lower;
   if (xx < lower+Range*0.01) Status = 1;
   if (xx > upper-Range*0.01) Status = 1;
   OutFile1 << lower << " " << upper << " ";
   if (Status == 1) OutFile1 << "*" << " ";
   RETURN_ARRAYS_DECREMENT();
   return (Status);
  }
#include <admodel.h>
#include <contrib.h>

  extern "C"  {
    void ad_boundf(int i);
  }
#include <gdbprintlib.cpp>

#include <gmacs.htp>

model_data::model_data(int argc,char * argv[]) : ad_comm(argc,argv)
{
  if (0){
     //Testing selectivity using "constant" values
    cout<<"|---------------------------------------|"<<endl;
    cout<<"| Testing sandbox using constant values |"<<endl;
    cout<<"|---------------------------------------|"<<endl;
    class gsm::Selex<dvector> *pSLX;      
    dvector z(1,32);
    for (int i=z.indexmin();i<=z.indexmax();i++) z(i) = 27.5+(i-1)*5.0;
    cout<<"--Cubic Spline"<<endl;
    dvector x_knts(1,5);
    x_knts[1]=z[1]; for (int i=1;i<=4;i++) x_knts[i+1] = z[8*i];
    dvector y_vals = 1.0/(1.0+exp(-(x_knts-100.0)/30.0));
    cout<<"x_knts = "<<x_knts<<endl;
    cout<<"y_vals = "<<y_vals<<endl;
    pSLX = new class gsm::SelectivitySpline<dvector,dvector>(y_vals,x_knts);
    cout<<"z        = "<<x_knts<<endl;
    cout<<"sel      = "<<pSLX->Selectivity(x_knts)<<endl;
    cout<<"z        = "<<z<<endl;
    cout<<"sel      = "<<pSLX->Selectivity(z)<<endl;
    cout<<"logsel   = "<<pSLX->logSelectivity(z)<<endl;
    cout<<"logselM1 = "<<pSLX->logSelexMeanOne(z)<<endl;
    cout<<"--change knots and y_vals to check reallocation"<<endl;
    dvector x_knts1(1,9);
    x_knts1[1]=z[1]; for (int i=1;i<=8;i++) x_knts1[i+1] = z[4*i];
    dvector y_vals1 = 1.0/(1.0+exp(-(x_knts1-100.0)/30.0));
    ((gsm::SelectivitySpline<dvector,dvector>*)pSLX)->initSpline(y_vals1,x_knts1);
    cout<<"z        = "<<x_knts1<<endl;
    cout<<"sel      = "<<pSLX->Selectivity(x_knts1)<<endl;
    cout<<"z        = "<<z<<endl;
    cout<<"sel      = "<<pSLX->Selectivity(z)<<endl;
    cout<<"logsel   = "<<pSLX->logSelectivity(z)<<endl;
    cout<<"logselM1 = "<<pSLX->logSelexMeanOne(z)<<endl;
    //exit(1);
    cout<<"--DoubleNormal"<<endl;
    double p1 = 30.0;
    double p2 = 100.0;
    double p3 = 50.0;
    pSLX = new class gsm::DoubleNormal<dvector,double>(p1,p2,p3);
    cout<<z<<endl;
    cout<<pSLX->Selectivity(z)<<endl;
    cout<<pSLX->logSelectivity(z)<<endl;
    cout<<pSLX->logSelexMeanOne(z)<<endl;
    cout<<"--DoubleNormal4"<<endl;
    p1 = 30.0;
    p2 = 100.0;
    p3 = 50.0;
    double p4 = 130.0;
    pSLX = new class gsm::DoubleNormal4<dvector,double>(p1,p2,p3,p4);
    cout<<z<<endl;
    cout<<pSLX->Selectivity(z)<<endl;
    cout<<pSLX->logSelectivity(z)<<endl;
    cout<<pSLX->logSelexMeanOne(z)<<endl;
    cout<<"--Uniform"<<endl;
    pSLX = new class gsm::UniformCurve<dvector>();
    cout<<z<<endl;
    cout<<pSLX->Selectivity(z)<<endl;
    cout<<pSLX->logSelectivity(z)<<endl;
    cout<<pSLX->logSelexMeanOne(z)<<endl;
    cout<<"--Uniform0"<<endl;
    pSLX = new class gsm::Uniform0Curve<dvector>();
    cout<<z<<endl;
    cout<<pSLX->Selectivity(z)<<endl;
    cout<<pSLX->logSelectivity(z)<<endl;
    cout<<pSLX->logSelexMeanOne(z)<<endl;
    exit(1);
  }
  simflag = 0;
  rseed = 0;
  int opt,on;
  
  sexes += "male";
  sexes += "female";
  /**
   * @brief command line option for simulating data.
  **/
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-sim",opt))>-1 )
   {
    simflag = 1;
    rseed = atoi(ad_comm::argv[on+1]);
   }
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-i",opt))>-1 )
   {
    cout << "\n";
    cout << "  +----------------------------------------------------------+\n";
    cout << "  | CONTRIBUTIONS (code and intellectual)                    |\n";
    cout << "  +----------------------------------------------------------+\n";
    cout << "  | Name:                        Organization:               |\n";
    cout << "  | James Ianelli                NOAA-NMFS                   |\n";
    cout << "  | D'Arcy Webber                Quantifish                  |\n";
    cout << "  | Steven Martell               SeaState                    |\n";
    cout << "  | Jack Turnock                 NOAA-NMFS                   |\n";
    cout << "  | Jie Zheng                    ADF&G                       |\n";
    cout << "  | Hamachan Hamazaki            ADF&G                       |\n";
    cout << "  | Athol Whitten                University of Washington    |\n";
    cout << "  | Andre Punt                   University of Washington    |\n";
    cout << "  | Dave Fournier                Otter Research              |\n";
    cout << "  | John Levitt                  Mathemetician               |\n";
    cout << "  | William Stockhausen          NOAA-NMFS                   |\n";
    cout << "  +----------------------------------------------------------+\n";
    cout << "\n";
    cout << "  +----------------------------------------------------------+\n";
    cout << "  | FINANCIAL SUPPORT                                        |\n";
    cout << "  +----------------------------------------------------------+\n";
    cout << "  | Financial support for this project was provided by the   |\n";
    cout << "  | National Marine Fisheries Service, the Bering Sea        |\n";
    cout << "  | Fisheries Research Foundation, ...                       |\n";
    cout << "  +----------------------------------------------------------+\n";
    cout << "\n";
    cout << "  +----------------------------------------------------------+\n";
    cout << "  | DOCUMENTATION                                            |\n";
    cout << "  +----------------------------------------------------------+\n";
    cout << "  | online api: http://seacode.github.io/gmacs/index.html    |\n";
    cout << "  +----------------------------------------------------------+\n";
    cout << "\n";
    exit(1);
   }
  // Command line option here to do retrospective analysis
  if ( (on=option_match(ad_comm::argc,ad_comm::argv, "-retro", opt))>-1 )
   {
    cout << "\n";
    cout << "  +----------------------------------------------------------+\n";
    cout << "  | Running retrospective model with " << ad_comm::argv[on+1] << " recent yrs removed |\n";
    cout << "  +----------------------------------------------------------+\n";
    cout << "  | YET TO BE IMPLEMENTED                                    |\n";
    cout << "  +----------------------------------------------------------+\n";
    exit(1);
   }
  datafile.allocate("datafile");
  controlfile.allocate("controlfile");
  projectfile.allocate("projectfile");
  IsJittered.allocate("IsJittered");
  sdJitter.allocate("sdJitter");
 if (IsJittered==1) cout << "Jittering with sd: " << sdJitter << endl;
 ad_comm::change_datafile_name(datafile); WriteFileName(datafile); WriteFileName(controlfile); WriteFileName(projectfile);
 cout << "+----------------------+" << endl;
 cout << "| Reading data file    |" << endl;
 cout << "+----------------------+" << endl;
 cout << " * Model dimensions" << endl;
  syr.allocate("syr");
  nyr.allocate("nyr");
 nyrRetro = nyr;
  nseason.allocate("nseason");
  nfleet.allocate("nfleet");
  nsex.allocate("nsex");
 if (nsex != 1 & nsex != 2)
  { cout << "nsex can only be 1 or 2; STOPPING" << endl; exit(1); }
  nshell.allocate("nshell");
  nmature.allocate("nmature");
  nclass.allocate("nclass");
  season_recruitment.allocate("season_recruitment");
  season_growth.allocate("season_growth");
  season_ssb.allocate("season_ssb");
  season_N.allocate("season_N");
  nSizeSex.allocate(1,nsex,"nSizeSex");
  n_grp = nsex * nshell * nmature;
  nlikes = 5;                                              ///> catch, cpue, size comps, recruits, molt increments
  WRITEDAT(syr); WRITEDAT(nyrRetro); WRITEDAT(nseason);
  WRITEDAT(nfleet); WRITEDAT(nsex); WRITEDAT(nshell); WRITEDAT(nmature); WRITEDAT(nclass);
  WRITEDAT(season_recruitment); WRITEDAT(season_growth);
  WRITEDAT(season_ssb); WRITEDAT(season_N);
  WRITEDAT(nSizeSex);
  // Check at least one matches nclass
  if (max(nSizeSex)!=nclass) { cout << "One of the maximum size-classes needs to match nclass; STOPPING" << endl; exit(1); }
  isex.allocate(1,n_grp);
  ishell.allocate(1,n_grp);
  imature.allocate(1,n_grp);
  pntr_hmo.allocate(1,nsex,1,nmature,1,nshell);
  int h,m,o;
  int hmo=1;
  for ( h = 1; h <= nsex; h++ )
   for ( m = 1; m <= nmature; m++ )
    for ( o = 1; o <= nshell; o++ )
     {
      isex(hmo) = h;
      ishell(hmo) = o;
      imature(hmo) = m;
      pntr_hmo(h,m,o) = hmo++;
     }
  size_breaks.allocate(1,nclass+1,"size_breaks");
  mid_points.allocate(1,nclass);
WRITEDAT(size_breaks);
 cout << " * Natural mortality" << endl;
  m_prop_type.allocate("m_prop_type");
 if (m_prop_type != 1 & m_prop_type != 2)
  { cout << "m_prop_type can only be 1 or 2; STOPPING" << endl; exit(1); }
   m_dim = 1;
   if ( m_prop_type == 2 ) m_dim = nyr - syr + 1;
  m_prop_in.allocate(1,m_dim,1,nseason,"m_prop_in");
 gmacs_data << "# Natural mortality per season input type (1 = vector by season, 2 = matrix by season/year)" << endl << " 2" << endl;
  m_prop.allocate(syr,nyrRetro,1,nseason);
   switch ( m_prop_type )
    {
     // vector by season
     case 1:
      for ( int i = syr; i <= nyrRetro; i++ )
       for ( int j = 1; j <= nseason; j++ )
         m_prop(i,j) = m_prop_in(1,j);
      break;
     // matrix by year and season
     case 2:
      for ( int i = syr; i <= nyrRetro; i++ )
       for ( int j = 1; j <= nseason; j++ )
         m_prop(i,j) = m_prop_in(i-syr+1,j);
      break;
    }
    for ( int i = syr; i <= nyrRetro; i++ )
     if ( sum(m_prop(i)) > 1.0000001 || sum(m_prop(i)) < 0.999999 )
      {
       cout << "Error: the proportion of natural mortality applied each season (in the .dat file) does not sum to 1! It sums to " << sum(m_prop(i)) << endl;
        exit(1);
      }
   gmacs_data << "# Proportion of the total natural mortality to be applied each season" << endl;
   for (int i=syr;i<=nyrRetro;i++)
    gmacs_data << m_prop(i) << " # " << i << endl;
 for (int ifleet=1;ifleet<=nfleet;ifleet++) 
  {
      *(ad_comm::global_datafile) >> anystring;
      fleetname+=anystring;
  }
 WRITEDAT(fleetname)
  season_type.allocate(1,nseason,"season_type");
 gmacs_data << "#Season type: Set to 1 for continuous F and 0 for instantanous F" << endl;
 gmacs_data << season_type << endl;
 cout << " * Catch data" << endl;
  nCatchDF.allocate("nCatchDF");
  nCatchRows.allocate(1,nCatchDF,"nCatchRows");
  dCatchData.allocate(1,nCatchDF,1,nCatchRows,1,11,"dCatchData");
 WRITEDAT(nCatchDF); 
 gmacs_data << "# Number of lines for each group (this is not correct for retrospective analyses)" << endl;
 gmacs_data << nCatchRows << endl;
 gmacs_data << "## Sex: 1 = male, 2 = female, 0 = both" << endl;
 gmacs_data << "## Type of catch: 1 = retained, 2 = discard, 0 = total" << endl;
 gmacs_data << "## Units of catch: 1 = biomass, 2 = numbers" << endl;
 gmacs_data << "## Mult: 1= use data as they are, 2 = multiply by this number (e.g., lbs to kg)" << endl;
 gmacs_data << "# Year Season Fleet Sex Obs CV Units Mult Effort Discard_mortality" << endl;
 for (int iCatOut=1;iCatOut<=nCatchDF;iCatOut++)
  for (int irow=1;irow<=nCatchRows(iCatOut); irow++)
   {
    if (dCatchData(iCatOut,irow,1) <= nyrRetro)
     {
      gmacs_data << dCatchData(iCatOut,irow) << " ";
      anystring = "# " + fleetname(dCatchData(iCatOut,irow,3));
      if (dCatchData(iCatOut,irow,4)==1) anystring = anystring +"_male";
      if (dCatchData(iCatOut,irow,4)==2) anystring = anystring +"_female";
      if (dCatchData(iCatOut,irow,7)==0) anystring = anystring +"_total";
      if (dCatchData(iCatOut,irow,7)==1) anystring = anystring +"_retained";
      if (dCatchData(iCatOut,irow,7)==2) anystring = anystring +"_discard";
      if (dCatchData(iCatOut,irow,6) <= 0)
       {
        cout << "Error: CV of catch is zero (or less) for group " << iCatOut << " row " << irow << endl;
        exit(1);
       }
      gmacs_data << anystring << endl;
     }
   }
  obs_catch.allocate(1,nCatchDF,1,nCatchRows);
  obs_effort.allocate(1,nCatchDF,1,nCatchRows);
  dCatchData_out.allocate(1,nCatchDF,syr,nyr,1,11);
  obs_catch_out.allocate(1,nCatchDF,syr,nyr);
  catch_cv.allocate(1,nCatchDF,1,nCatchRows);
  catch_dm.allocate(1,nCatchDF,1,nCatchRows);
  catch_mult.allocate(1,nCatchDF,1,nCatchRows);
  for ( int k = 1; k <= nCatchDF; k++ )
   {
    catch_mult(k) = column(dCatchData(k),9);
    obs_catch(k)  = column(dCatchData(k),5);
    catch_cv(k)   = column(dCatchData(k),6);
    catch_dm(k)   = column(dCatchData(k),11);
    obs_catch(k)  = elem_prod(obs_catch(k), catch_mult(k));         ///> rescale catch by multiplier
    obs_effort(k) = column(dCatchData(k),10);
   }
  ECHO(obs_catch);
  ECHO(catch_cv);
  nFparams.allocate(1,nfleet);
  nYparams.allocate(1,nfleet);
  fhit.allocate(syr,nyrRetro,1,nseason,1,nfleet);
  yhit.allocate(syr,nyrRetro,1,nseason,1,nfleet);
  dmr.allocate(syr,nyrRetro,1,nfleet);
  nFparams.initialize();
  nYparams.initialize();
  fhit.initialize();
  yhit.initialize();
  dmr.initialize();
  for ( int k = 1; k <= nCatchDF; k++ )
   {
    for ( int i = 1; i <= nCatchRows(k); i++ )
     if (dCatchData(k)(i,1) <= nyrRetro)
      {
       int y = dCatchData(k)(i,1);                          ///> year
       int j = dCatchData(k)(i,2);                          ///> season
       int g = dCatchData(k)(i,3);                          ///> fleet
       int h = dCatchData(k)(i,4);                          ///> sex
       // Check whether the fleet is instantaneous but natural mortality in the relevant period is not zero!
       if (season_type(j) == INSTANT_F & m_prop(y,j) > 0)
        {
         cout << "The proportion of M should be zero for season " << j << " in year " << y << endl;
         exit(1);
        }
       if ( !fhit(y,j,g) )
        {
         fhit(y,j,g) ++;
         nFparams(g) ++;
         dmr(y,g) = catch_dm(k)(i);
        }
       if ( !yhit(y,j,g) && h == 2 )
        {
         yhit(y,j,g) ++;
         nYparams(g) ++;
         dmr(y,g) = catch_dm(k)(i);
        }
      }
   }
  ECHO(nFparams); ECHO(nYparams); ECHO(fhit); ECHO(yhit); ECHO(dmr);
  // Check for errors in discard rate assumptions
  for ( int k = 1; k <= nCatchDF; k++ )
   for ( int i = 1; i <= nCatchRows(k); i++ )
    if (dCatchData(k)(i,1) <= nyrRetro)
     {
      int y = dCatchData(k)(i,1);                           ///> year
      int g = dCatchData(k)(i,3);                           ///> fleet
      if (catch_dm(k)(i) != dmr(y,g))
       { cout << "ERROR: discard rates do not match: year " << y << " " << endl; exit(1); }
     }
  // Create the dCatchData_out object for output and plotting in R, this object simply fills in the years that don't have data with zero catch
  dCatchData_out.initialize();
  obs_catch_out.initialize();
  for ( int k = 1; k <= nCatchDF; k++ )
   for ( int i = syr; i <= nyrRetro; i++ )
    {
     dCatchData_out(k,i,1) = i; // Year
     int j = 1;
     for ( int ii = 1; ii <= nCatchRows(k); ii++ )
      {
       if ( i == dCatchData(k,ii,1) ) // year index
        {
         j = ii;
         obs_catch_out(k,i)    = dCatchData(k,ii,5); // Obs
         dCatchData_out(k,i,5) = dCatchData(k,ii,5); // Obs
         dCatchData_out(k,i,6) = dCatchData(k,ii,6); // CV
         dCatchData_out(k,i,9)  = dCatchData(k,j,9); // Mult
         dCatchData_out(k,i,10) = dCatchData(k,j,10); // Effort
         dCatchData_out(k,i,11) = dCatchData(k,j,11); // Discard mortality
        }
      }
     // Replicate these variables
     dCatchData_out(k,i,2) = dCatchData(k,j,2); // Season
     dCatchData_out(k,i,3) = dCatchData(k,j,3); // Fleet
     dCatchData_out(k,i,4) = dCatchData(k,j,4); // Sex
     dCatchData_out(k,i,7) = dCatchData(k,j,7); // Type
     dCatchData_out(k,i,8) = dCatchData(k,j,8); // Units
    }
 cout << " * Abundance data" << endl;
  nSurveys.allocate("nSurveys");
  nSurveyRows.allocate("nSurveyRows");
  dSurveyData.allocate(1,nSurveyRows,0,8,"dSurveyData");
  obs_cpue.allocate(1,nSurveyRows);
  cpue_cv.allocate(1,nSurveyRows);
  cpue_sd.allocate(1,nSurveyRows);
  cpue_cv_add.allocate(1,nSurveyRows);
  obs_cpue = column(dSurveyData,6);
  cpue_cv  = column(dSurveyData,7);
  cpue_sd  = sqrt(log(1.0 + square(cpue_cv)));
  WRITEDAT(nSurveys); 
  gmacs_data << "# Number of lines for each index (this is not correct for retrospective analyses)" << endl;
  gmacs_data << nSurveyRows << endl;; 
  gmacs_data << "## Index: One q is estimated for each index (the number of index values should match nSurveys" << endl;
  gmacs_data << "## Sex: 1 = male, 2 = female, 0 = both" << endl;
  gmacs_data << "## Maturity: 1 = mature, 2 = immature, 0 = both" << endl;
  gmacs_data << "## Units of survey: 1 = biomass, 2 = numbers" << endl;
  gmacs_data << "# Index Year Season Fleet Sex Maurity Obs CV Units" << endl;
  for (int irow=1;irow<=nSurveyRows; irow++)
   if (dSurveyData(irow,1) <= nyrRetro || (dSurveyData(irow,1) == nyrRetro+1 & dSurveyData(irow,2) == 1))
    {
     gmacs_data << dSurveyData(irow) << " ";
     anystring = "# " + fleetname(dSurveyData(irow,3));
     if (dSurveyData(irow,4)==BOTHSEX)          anystring = anystring +"_male+female";
     if (dSurveyData(irow,4)==MALESANDCOMBINED) anystring = anystring +"_male";
     if (dSurveyData(irow,4)==FEMALES)          anystring = anystring +"_female";
     if (dSurveyData(irow,5)==BOTHMATURE) anystring = anystring +"_immature+mature";
     if (dSurveyData(irow,5)==IMMATURE)   anystring = anystring +"_immature";
     if (dSurveyData(irow,5)==MATURE)     anystring = anystring +"_mature";
     gmacs_data << anystring << endl;
    }
  ECHO(obs_cpue); ECHO(cpue_cv); ECHO(cpue_sd);
 cout << " * Size composition data" << endl;
  nSizeComps_in.allocate("nSizeComps_in");
  nSizeCompRows_in.allocate(1,nSizeComps_in,"nSizeCompRows_in");
  nSizeCompCols_in.allocate(1,nSizeComps_in,"nSizeCompCols_in");
  d3_SizeComps_in.allocate(1,nSizeComps_in,1,nSizeCompRows_in,-7,nSizeCompCols_in,"d3_SizeComps_in");
  d3_obs_size_comps_in.allocate(1,nSizeComps_in,1,nSizeCompRows_in,1,nSizeCompCols_in);
  size_comp_sample_size_in.allocate(1,nSizeComps_in,1,nSizeCompRows_in);
  size_comp_year_in.allocate(1,nSizeComps_in,1,nSizeCompRows_in);
  size_comp_season_in.allocate(1,nSizeComps_in,1,nSizeCompRows_in);
  for ( int kk = 1; kk <= nSizeComps_in; kk++ )
   {
    dmatrix tmp = trans(d3_SizeComps_in(kk)).sub(1,nSizeCompCols_in(kk));
    d3_obs_size_comps_in(kk) = trans(tmp);
    size_comp_sample_size_in(kk) = column(d3_SizeComps_in(kk),0);
    size_comp_year_in(kk) = column(d3_SizeComps_in(kk),-7);
    size_comp_season_in(kk) = column(d3_SizeComps_in(kk),-6);
   }
  WRITEDAT(nSizeComps_in); WRITEDAT(nSizeCompRows_in); WRITEDAT(nSizeCompCols_in); 
  gmacs_data << "## Sex: 1 = male, 2 = female, 0 = both" << endl;
  gmacs_data << "## Type of catch: 1 = retained, 2 = discard, 0 = total" << endl;
  gmacs_data << "## Shell: 1 = newshell, 2 = oldshell, 0 = both" << endl;
  gmacs_data << "## Maturity: 1 = immature, 2 = mature, 0 = both" << endl;
  gmacs_data << "## Stage1_EffN: the stage-1 effective sample size (this can be modified in the CTL file)" << endl;
  gmacs_data << "# Year Season Fleet Sex Type Shell Maturity Stage1_EffN Data" << endl;
  float testtotal;
  for (int irow=1;irow<=nSizeComps_in; irow++)
   for (int jrow=1;jrow<=nSizeCompRows_in(irow);jrow++)
    if (d3_SizeComps_in(irow,jrow,-7) <= nyrRetro || (d3_SizeComps_in(irow,jrow,-7) == nyrRetro+1 & d3_SizeComps_in(irow,jrow,-6) == 1) )
     {
      gmacs_data << d3_SizeComps_in(irow,jrow) << " ";
      anystring = "# " + fleetname(d3_SizeComps_in(irow,jrow,-5));
      testtotal = 0;
      for (int ilen=1;ilen<=nSizeCompCols_in(irow);ilen++) testtotal += d3_SizeComps_in(irow,jrow,ilen);
      if (testtotal <=0) 
       {
        cout << "Error: one of your rows of length data has no data (group " << irow << "; row "<< jrow << ")" << endl;
        exit(1);
       }
      int h = d3_SizeComps_in(irow,jrow,-4);
      if (h==0 & nSizeCompCols_in(irow) != nclass)
       {
        cout << "Error: the specified sex and the number of classes is mis-matched (group " << irow << "; row "<< jrow << ")" << endl;
        exit(1);
       }
      if (h!=0 & nSizeCompCols_in(irow) != nSizeSex(h))
       {
        cout << "Error: the specified sex and the number of classes is mis-matched (group " << irow << "; row "<< jrow << ")" << endl;
        exit(1);
       }
    
      if (d3_SizeComps_in(irow,jrow,-4)==BOTHSEX)          anystring = anystring +"_male+female";
      if (d3_SizeComps_in(irow,jrow,-4)==MALESANDCOMBINED) anystring = anystring +"_male";
      if (d3_SizeComps_in(irow,jrow,-4)==FEMALES)          anystring = anystring +"_female";
      if (d3_SizeComps_in(irow,jrow,-3)==TOTALCATCH)       anystring = anystring +"_total";
      if (d3_SizeComps_in(irow,jrow,-3)==RETAINED)         anystring = anystring +"_retained";
      if (d3_SizeComps_in(irow,jrow,-3)==DISCARDED)        anystring = anystring +"_discard";
      if (d3_SizeComps_in(irow,jrow,-2)==UNDET_SHELL)      anystring = anystring +"_all_shell";
      if (d3_SizeComps_in(irow,jrow,-2)==NEW_SHELL)        anystring = anystring +"_newshell";
      if (d3_SizeComps_in(irow,jrow,-2)==OLD_SHELL)        anystring = anystring +"_oldshell";
      if (d3_SizeComps_in(irow,jrow,-1)==BOTHMATURE)       anystring = anystring +"_immature+mature";
      if (d3_SizeComps_in(irow,jrow,-1)==IMMATURE)         anystring = anystring +"_immature";
      if (d3_SizeComps_in(irow,jrow,-1)==MATURE)           anystring = anystring +"_mature";    
      gmacs_data << anystring << endl;
     } 
  ECHO(d3_obs_size_comps_in);
 cout << " * Growth data" << endl;
  GrowthObsType.allocate("GrowthObsType");
 if (GrowthObsType != NOGROWTH_DATA & GrowthObsType != GROWTHINC_DATA & GrowthObsType != GROWTHCLASS_DATA)
  { cout << "GrowthObsType can only be 0,1 or 2; STOPPING" << endl; exit(1); }
  nGrowthObs.allocate("nGrowthObs");
if (GrowthObsType==GROWTHINC_DATA) NGrowthInputs = 4; else NGrowthInputs = 8;
if(GrowthObsType==GROWTHINC_DATA) gmacs_data << "## Size increments" << endl;
if(GrowthObsType==GROWTHCLASS_DATA) gmacs_data << "## size-at-release, size-at-recaptures, and time-at-liberty" << endl;
  dGrowthData.allocate(1,nGrowthObs,1,NGrowthInputs,"dGrowthData");
  dPreMoltSize.allocate(1,nGrowthObs);
  iMoltIncSex.allocate(1,nGrowthObs);
  dMoltInc.allocate(1,nGrowthObs);
  dMoltIncCV.allocate(1,nGrowthObs);
  mle_alpha.allocate(1,nsex);
  mle_beta.allocate(1,nsex);
  iMoltInitSizeClass.allocate(1,nGrowthObs);
  iMoltEndSizeClass.allocate(1,nGrowthObs);
  iMoltTimeAtLib.allocate(1,nGrowthObs);
  iMoltTrans.allocate(1,nGrowthObs);
  iMoltFleetRecap.allocate(1,nGrowthObs);
  iMoltYearRecap.allocate(1,nGrowthObs);
  iMoltSampSize.allocate(1,nGrowthObs);
  MaxGrowTimeLibSex.allocate(1,nsex);
 MaxGrowTimeLibSex.initialize();
 MaxGrowTimeLib = 0;
  if (GrowthObsType==GROWTHINC_DATA)
   {
    dPreMoltSize = column(dGrowthData,1);
    iMoltIncSex  = ivector(column(dGrowthData,2));
    dMoltInc     = column(dGrowthData,3);
    dMoltIncCV   = column(dGrowthData,4);
    dvector xybar(1,nsex);
    dvector xx(1,nsex);
    dvector xbar(1,nsex);
    dvector ybar(1,nsex);
    ivector nh(1,nsex);
    nh.initialize();
    xybar.initialize();
    xbar.initialize();
    ybar.initialize();
    xx.initialize();
    // MLE estimates for alpha and beta for the linear growth increment model.
    if ( nGrowthObs > 0 )
     {
      for ( int i = 1; i <= nGrowthObs; i++ )
       {
        int h = iMoltIncSex(i);
        nh(h)++;
        xybar(h) += dPreMoltSize(i) * dMoltInc(i);
        xbar(h)  += dPreMoltSize(i);
        ybar(h)  += dMoltInc(i);
        xx(h)    += square(dPreMoltSize(i));
       }
      for ( h = 1; h <= nsex; h++ )
       {
        xybar(h) /= nh(h);
        xbar(h) /= nh(h);
        ybar(h) /= nh(h);
        xx(h) /= nh(h);
        double slp = (xybar(h) - xbar(h)*ybar(h)) / (xx(h) - square(xbar(h)));
        double alp = ybar(h) - slp*xbar(h);
        mle_alpha(h) = alp;
        mle_beta(h) = -slp;
       }
     }
   }
  if (GrowthObsType==GROWTHCLASS_DATA)
   {
    int iclass;
    int h2;
    iMoltIncSex  = ivector(column(dGrowthData,2));
    iMoltTimeAtLib  = ivector(column(dGrowthData,4));
    iMoltTrans = ivector(column(dGrowthData,5));
    iMoltFleetRecap = ivector(column(dGrowthData,6));
    iMoltYearRecap = ivector(column(dGrowthData,7));
    iMoltSampSize = ivector(column(dGrowthData,8));
    for (int i = 1; i <= nGrowthObs; i++)
     {
      h2 = iMoltIncSex(i);
      iclass = -1;
      for (int j = 1; j <=nclass; j++)
       if (dGrowthData(i,1) >= size_breaks(j) &  dGrowthData(i,1) < size_breaks(j+1)) iclass = j;
      iMoltInitSizeClass(i) = iclass;
      if (iclass == -1) { cout << "Error: release size out of range; row" << i << endl; exit(1); }
      iclass = -1;
      for (int j = 1; j <=nclass; j++)
       if (dGrowthData(i,3) >= size_breaks(j) &  dGrowthData(i,3) < size_breaks(j+1)) iclass = j;
      iMoltEndSizeClass(i) = iclass;
      if (iclass == -1) { cout << "Error: recapture size out of range; row " << i << endl; exit(1); }
      if (iMoltEndSizeClass(i) < iMoltInitSizeClass(i)) { cout << "Error: recapture size less than recapture size; row " << i << endl; exit(1); }
      if (MaxGrowTimeLibSex(h2) < iMoltTimeAtLib(i)) MaxGrowTimeLibSex(h2) = iMoltTimeAtLib(i);
      if (MaxGrowTimeLib < iMoltTimeAtLib(i)) MaxGrowTimeLib = iMoltTimeAtLib(i);
     }
   }
  WRITEDAT(GrowthObsType); WRITEDAT(nGrowthObs); 
  if(GrowthObsType==GROWTHINC_DATA) gmacs_data << "# Pre-molt_size Sex size-increment CV" << endl;
  if(GrowthObsType==GROWTHCLASS_DATA) gmacs_data << "# Size-at-release Sex Size-at-recapture Time-at-liberty fleet-at-recapture year-at-recapture sample_size" << endl;
  gmacs_data << dGrowthData << endl;
  if (GrowthObsType==GROWTHINC_DATA)
   {  ECHO(dPreMoltSize); ECHO(iMoltIncSex); ECHO(dMoltInc); ECHO(dMoltIncCV); }
  if (GrowthObsType==GROWTHCLASS_DATA)
   {  ECHO(iMoltIncSex);ECHO(iMoltInitSizeClass); ECHO(iMoltEndSizeClass); ECHO(iMoltTimeAtLib); ECHO(iMoltFleetRecap); ECHO(iMoltYearRecap); ECHO(iMoltSampSize);}
  eof.allocate("eof");
 WRITEDAT(eof);
 if ( eof != 9999 ) {cout << "Error reading data" << endl; exit(1);}
 cout << "end of data section" << endl;
 ad_comm::change_datafile_name(controlfile);
 cout << "+----------------------+" << endl;
 cout << "| Reading control file |" << endl;
 cout << "+----------------------+" << endl;
 cout << " * Key parameter controls" << endl;
  ntheta.allocate("ntheta");
  theta_control.allocate(1,ntheta,1,7,"theta_control");
 WriteCtl(ntheta)
 gmacs_ctl << "# Core parameters" << endl;
 gmacs_ctl << "## Initial: Initial value for the parameter (must lie between lower and upper)" << endl;
 gmacs_ctl << "## Lower & Upper: Range for the parameter" << endl;
 gmacs_ctl << "## Phase: Set equal to a negative number not to estimate" << endl;
 gmacs_ctl << "## Prior type:"  << endl;
 gmacs_ctl << "## 0: Uniform   - parameters are the range of the uniform prior"  << endl;
 gmacs_ctl << "## 1: Normal    - parameters are the mean and sd" << endl;
 gmacs_ctl << "## 2: Lognormal - parameters are the mean and sd of the log" << endl;
 gmacs_ctl << "## 3: Beta      - parameetrs are the two beta parameters [see dbeta]" << endl;
 gmacs_ctl << "## 4: Gamma     - parameetrs are the two gamma parameters [see dgamma]" << endl;
 gmacs_ctl << "# Initial_value Lower_bound Upper_bound Phase Prior_type Prior_1 Prior_2" << endl;
 gmacs_ctl << theta_control << endl;
  theta_ival.allocate(1,ntheta);
  theta_lb.allocate(1,ntheta);
  theta_ub.allocate(1,ntheta);
  theta_phz.allocate(1,ntheta);
  theta_ival = column(theta_control,1);
  theta_lb   = column(theta_control,2);
  theta_ub   = column(theta_control,3);
  theta_phz  = ivector(column(theta_control,4));
 cout << " * Allometry" << endl;
  lw_type.allocate("lw_type");
 WriteCtl(lw_type);
 if (lw_type < 1 | lw_type > 3)
  { cout << "length-weight type can only be 1,2 or 3; STOPPING" << endl; exit(1); }
  lw_dim = nsex;
  if ( lw_type == LW_MATRIX ) lw_dim = nsex * (nyr+1 - syr + 1);
  lw_dim2 = nsex;
  if ( lw_type == LW_MATRIX ) lw_dim2 = nsex * (nyrRetro+1 - syr + 1);
  lw_alfa.allocate(1,nsex);
  lw_beta.allocate(1,nsex);
  mean_wt_in.allocate(1,lw_dim,1,nclass);
  mean_wt.allocate(1,nsex,syr,nyrRetro+1,1,nclass);
  if (lw_type==LW_RELATIONSHIP)
   {
    for (int h=1;h<=nsex;h++) *(ad_comm::global_datafile) >> lw_alfa(h);
    for (int h=1;h<=nsex;h++) *(ad_comm::global_datafile) >> lw_beta(h);
    WriteCtl(lw_alfa); WriteCtl(lw_beta);
   }
  if (lw_type==LW_VECTOR || lw_type==LW_MATRIX)
   {
    for (int I=1;I<=lw_dim;I++)
     for ( int l = 1; l <= nclass; l++ ) *(ad_comm::global_datafile) >> mean_wt_in(I,l);
    gmacs_ctl << "# mean_wt_inv" << endl; 
    for (int I=1;I<=lw_dim2;I++)
     gmacs_ctl << mean_wt_in(I) << endl;
   }
  mid_points = size_breaks(1,nclass) + 0.5 * first_difference(size_breaks);
  switch ( lw_type )
   {
    // allometry
    case LW_RELATIONSHIP:
     for ( int h = 1; h <= nsex; h++ )
      for ( int i = syr; i <= nyrRetro+1; i++ )
       mean_wt(h,i) = lw_alfa(h) * pow(mid_points, lw_beta(h));
     break;
    // vector by sex
    case LW_VECTOR:
     for ( int h = 1; h <= nsex; h++ )
      for ( int i = syr; i <= nyrRetro+1; i++ )
       for ( int l = 1; l <= nclass; l++ )
        mean_wt(h,i,l) = mean_wt_in(h,l);
     break;
    // matrix by sex
    case LW_MATRIX:
     for ( int h = 1; h <= nsex; h++ )
      for ( int i = syr; i <= nyrRetro+1; i++ )
       for ( int l = 1; l <= nclass; l++ )
        mean_wt(h,i,l) = mean_wt_in(i-syr+1,l);
     break;
   }
  ECHO(mean_wt);
 cout << " * Maturity definition" << endl;
  maturity.allocate(1,nsex,1,nclass,"maturity");
  WriteCtl(maturity);
 cout << " * Legal definition" << endl;
  legal.allocate(1,nsex,1,nclass,"legal");
  WriteCtl(legal);
 cout << " * Growth parameter controls" << endl;
 gmacs_ctl << "## Options for the growth matrix" << endl;
 gmacs_ctl << "## 1: Fixed growth transition matrix (requires molt probability)" << endl;
 gmacs_ctl << "## 2: Fixed size transition matrix (molt probability is ignored)" << endl;
 gmacs_ctl << "## 3: Growth increment is gamma distributed" << endl;
 gmacs_ctl << "## 4: Size after growth is gamma distributed" << endl;
 gmacs_ctl << "## 5: kappa varies among individuals" << endl;
 gmacs_ctl << "## 6: Linf varies among individuals" << endl;
 gmacs_ctl << "## 7: kappa and Ling varies among individuals" << endl;
 gmacs_ctl << "## 8: Growth increment is normally distributed" << endl;
  bUseCustomGrowthMatrix.allocate("bUseCustomGrowthMatrix");
 WriteCtl(bUseCustomGrowthMatrix);
 if (bUseCustomGrowthMatrix < 1 | bUseCustomGrowthMatrix > 8)
  { cout << "growth matrix type can only be 1-8; STOPPING" << endl; exit(1); }
 gmacs_ctl << "## Options for the growth increment model matrix" << endl;
 gmacs_ctl << "## 1: Linear" << endl;
 gmacs_ctl << "## 2: Individual" << endl;
 gmacs_ctl << "## 3: Individual (Same as 2)" << endl;
  bUseGrowthIncrementModel.allocate("bUseGrowthIncrementModel");
 if (bUseCustomGrowthMatrix == GROWTH_VARYK) bUseGrowthIncrementModel = GROWTH_VARYK;
 if (bUseCustomGrowthMatrix == GROWTH_VARYLINF) bUseGrowthIncrementModel = GROWTH_VARYLINF;
 if (bUseCustomGrowthMatrix == GROWTH_VARYKLINF) bUseGrowthIncrementModel = GROWTH_VARYKLINF;
 WriteCtl(bUseGrowthIncrementModel);
  bUseCustomMoltProbility.allocate("bUseCustomMoltProbility");
 WriteCtl(bUseCustomMoltProbility);
 if (bUseCustomGrowthMatrix == GROWTH_FIXEDSIZETRANS & bUseGrowthIncrementModel != FIXED_PROB_MOLT)
  {
   cout << "If the custom growth model = 1 molt probability must be 1; STOPPING" << endl; exit(1);
  }
  nSizeClassRec.allocate(1,nsex,"nSizeClassRec");
WriteCtl(nSizeClassRec);
  nSizeIncVaries.allocate(1,nsex,"nSizeIncVaries");
WriteCtl(nSizeIncVaries);
  nSizeIncChanges.allocate(1,nsex);
  nSizeIncChanges = nSizeIncVaries-1;
  maxSizeIncVaries = max(nSizeIncVaries);
  iYrsSizeIncChanges.allocate(1,nsex,1,nSizeIncChanges,"iYrsSizeIncChanges");
 gmacs_ctl << "# Start of the blocks in which molt increment changes (one row for each sex) - the first block starts in " << syr << endl;
 gmacs_ctl << "# Note: there is one less year than there are blocks" << endl;
 for (int isex=1;isex<=nsex;isex++)
  gmacs_ctl << iYrsSizeIncChanges(isex) << " # " << sexes(isex)  << endl;
  nMoltVaries.allocate(1,nsex,"nMoltVaries");
  nMoltChanges.allocate(1,nsex);
 WriteCtl(nMoltVaries);
 nMoltChanges = nMoltVaries-1;
  iYrsMoltChanges.allocate(1,nsex,1,nMoltChanges,"iYrsMoltChanges");
 gmacs_ctl << "# Start of the blocks in which molt probability changes (one row for each sex) - the first block starts in " << syr << endl;
 gmacs_ctl << "# Note: there is one less year than there are blocks" << endl;
 for (int isex=1;isex<=nsex;isex++)
  gmacs_ctl << iYrsMoltChanges(isex) << " # " << sexes(isex)  << endl;
  BetaParRelative.allocate("BetaParRelative");
WriteCtl(BetaParRelative);
  iYrIncChanges.allocate(1,nsex,syr,nyrRetro);
  for (int h=1;h<=nsex;h++)
   {
    for (int y=syr;y<=nyrRetro;y++) iYrIncChanges(h,y) = 1;
    for (int j=1;j<=nSizeIncChanges(h);j++)
     if (j!=nSizeIncChanges(h))
      for (int y=iYrsSizeIncChanges(h,j);y<=iYrsSizeIncChanges(h,j+1);y++) iYrIncChanges(h,y) = j+1;
     else
      for (int y=iYrsSizeIncChanges(h,j);y<=nyrRetro;y++) iYrIncChanges(h,y) = j+1;
   }
  ECHO(iYrIncChanges);
 if (GrowthObsType==GROWTHCLASS_DATA)
  for (int i=1;i<=nGrowthObs;i++)
   {
    int h = iMoltIncSex(i);
    int k = iMoltTrans(i);
    if (k < 0 || k > nSizeIncChanges(h)+1) 
     {
      cout << "Error: a specified size-transition matrix in the DAT file is out of range (line: " << i << ")" << endl;
      exit(1);
     }
   }
 nGrwth = 0; nSizeIncPar = 0;
 for (int h=1;h<=nsex;h++)
  {
   if (bUseGrowthIncrementModel==LINEAR_GROWTHMODEL) nSizeIncPar += nSizeIncVaries(h) * 3;
   if (bUseGrowthIncrementModel==INDIVIDUAL_GROWTHMODEL1) nSizeIncPar += nSizeIncVaries(h) * (nclass+1);
   if (bUseGrowthIncrementModel==INDIVIDUAL_GROWTHMODEL2) nSizeIncPar += nSizeIncVaries(h) * (nclass+1);
   if (bUseGrowthIncrementModel==GROWTH_VARYK) nSizeIncPar += nSizeIncVaries(h) * 3;
   if (bUseGrowthIncrementModel==GROWTH_VARYLINF) nSizeIncPar += nSizeIncVaries(h) * 3;
   if (bUseGrowthIncrementModel==GROWTH_VARYKLINF) nSizeIncPar += nSizeIncVaries(h) * 4;
   if (bUseCustomMoltProbility==LOGISTIC_PROB_MOLT) nGrwth += nMoltVaries(h) * 2;
   if (bUseCustomMoltProbility==FREE_PROB_MOLT) nGrwth += nMoltVaries(h) * (nclass);
  }
 nGrwth += nSizeIncPar;
 ECHO(nGrwth);
  Grwth_control.allocate(1,nGrwth,1,7,"Grwth_control");
 gmacs_ctl << "# Growth parameters" << endl;
 gmacs_ctl << "# Initial_value Lower_bound Upper_bound Phase Prior_type Prior_1 Prior_2" << endl;
 gmacs_ctl << Grwth_control << endl;
  Grwth_ival.allocate(1,nGrwth);
  Grwth_lb.allocate(1,nGrwth);
  Grwth_ub.allocate(1,nGrwth);
  Grwth_phz.allocate(1,nGrwth);
   Grwth_ival = column(Grwth_control,1);
   Grwth_lb   = column(Grwth_control,2);
   Grwth_ub   = column(Grwth_control,3);
   Grwth_phz  = ivector(column(Grwth_control,4));
  CustomGrowthMatrix.allocate(1,nsex,1,maxSizeIncVaries,1,nclass,1,nclass);
if (bUseCustomGrowthMatrix==GROWTH_FIXEDGROWTHTRANS || bUseCustomGrowthMatrix==GROWTH_FIXEDSIZETRANS)
 {
  for (int h=1;h<=nsex;h++)
   for (int i=1;i<=nSizeIncVaries(h);i++)
    {
     for (int class1=1;class1<= nSizeSex(h);class1++)
      for (int class2=1;class2<= nSizeSex(h);class2++)
      *(ad_comm::global_datafile) >>  CustomGrowthMatrix(h,i,class2,class1);
     WriteCtl( trans(CustomGrowthMatrix(h,i)) );
    }
 }
  CustomMoltProbabilityMatrix.allocate(1,nsex,1,nMoltVaries,1,nclass);
if (bUseCustomMoltProbility==FIXED_PROB_MOLT)
 {
  for (int h=1;h<=nsex;h++)
   for (int i=1;i<=nSizeIncVaries(h);i++)
    for (int l=1;l<= nSizeSex(h);l++)
     *(ad_comm::global_datafile) >>  CustomMoltProbabilityMatrix(h,i,l);
  gmacs_ctl << "#Pre-specified molt probability" << endl;;
  for (int h=1;h<=nsex;h++)
   for (int i=1;i<=nSizeIncVaries(h);i++)
    for (int l=1;l<= nSizeSex(h);l++)
     gmacs_ctl << CustomMoltProbabilityMatrix(h,i,l) << " ";
  gmacs_ctl << endl;
 }
 cout << " * Selectivity parameter controls" << endl;
 nslx_cols_in = 13;                                    //> number of columns in the control file to be read in
  slx_nsel_period_in.allocate(1,nfleet,"slx_nsel_period_in");
  slx_bsex_in.allocate(1,nfleet,"slx_bsex_in");
  slx_type_in.allocate(1,nsex,1,nfleet,"slx_type_in");
  slx_include_in.allocate(1,nfleet,"slx_include_in");
  slx_extra_in.allocate(1,nsex,1,nfleet,"slx_extra_in");
  ret_nret_period_in.allocate(1,nfleet,"ret_nret_period_in");
  ret_bsex_in.allocate(1,nfleet,"ret_bsex_in");
  ret_type_in.allocate(1,nsex,1,nfleet,"ret_type_in");
  slx_nret.allocate(1,nsex,1,nfleet,"slx_nret");
  ret_extra_in.allocate(1,nsex,1,nfleet,"ret_extra_in");
  slx_max_at_1_in.allocate(1,nfleet,"slx_max_at_1_in");
  gmacs_ctl << endl << "## Selectivity parameter controls" << endl;
  gmacs_ctl << "## Selectivity (and retention) types" << endl;
  gmacs_ctl << "##   0: Nonparameric selectivity (one parameter per class)" << endl;
  gmacs_ctl << "##   1: Nonparameric selectivity (one parameter per class, constant from last specified class)" << endl;
  gmacs_ctl << "##   2: Logistic selectivity (inflection point and slope)" << endl;
  gmacs_ctl << "##   3: Logistic selectivity (50% and 95% selection)" << endl;
  gmacs_ctl << "##   4: Double normal selectivity (3 parameters)" << endl;
  gmacs_ctl << "##   5: Flat equal to zero (1 parameter; phase must be negative)" << endl;
  gmacs_ctl << "##   6: Flat equal to one (1 parameter; phase must be negative)" << endl;
  gmacs_ctl << "##   7: Flat-topped double normal selectivity (4 parameters)" << endl;
  gmacs_ctl << "##   8: Decling logistic selectivity with initial values (50% and 95% selection plus extra)" << endl;
  gmacs_ctl << "##   9: Cubic-spline (specified with knots and values at knots)" << endl;
  gmacs_ctl << "## Extra (type 1): number of selectivity parameters to estimated" << endl;
  anystring = "# ";
  for ( int kk = 1; kk <= nfleet; kk++ ) anystring = anystring + " " + fleetname(kk);
  gmacs_ctl << anystring << endl;
  
  gmacs_ctl << slx_nsel_period_in << " # selectivity periods" << endl;
  gmacs_ctl << slx_bsex_in << " # sex specific selectivity (1=Yes, 0=No)" << endl;
  gmacs_ctl << slx_type_in << " # selectivity type (by sex)" << endl;
  gmacs_ctl << slx_include_in << " # selectivity within another gear" << endl;
  gmacs_ctl << slx_extra_in << " # extra parameters for each pattern" << endl;
  gmacs_ctl << ret_nret_period_in << " # retention periods " << endl;
  gmacs_ctl << ret_bsex_in << " # sex specific retention (1=Yes, 0=No)" << endl;
  gmacs_ctl << ret_type_in << " # retention type (by sex)" << endl;
  gmacs_ctl << slx_nret  << " # retention flag" << endl;
  gmacs_ctl << ret_extra_in << " # extra parameters for each pattern" << endl;
  gmacs_ctl << endl;
  
  // Work out how many selectivities we are dealing with, nfleet * nsex, plus any additonal sex-specific or time period selectivities
  nslx = 0;
  for ( int k = 1; k <= nfleet; k++ )
   {
    nslx += slx_nsel_period_in(k) * (1 + slx_bsex_in(k));
    nslx += ret_nret_period_in(k) * (1 + ret_bsex_in(k));
   }
  // Work out how many rows are in the selectivity/retention control inputs matrix based on the type of each selectivity and the number of blocks
  nslx_rows_in = 0;
  for ( int k = 1; k <= nfleet; k++ )
   {
    // Selectivity
    for ( int h = 1; h <= slx_bsex_in(k)+1; h++ )
     {
      if( slx_type_in(h,k) == SELEX_PARAMETRIC)             ///> parametric
       {
        nslx_rows_in += nclass * slx_nsel_period_in(k);
       }
      if( slx_type_in(h,k) == SELEX_COEFFICIENTS)           ///> coefficients
       {
        nslx_rows_in += slx_extra_in(h,k) * slx_nsel_period_in(k);
       }  
      if( slx_type_in(h,k) == SELEX_STANLOGISTIC)           ///> logistic has 2 parameters
       { 
        nslx_rows_in += 2 * slx_nsel_period_in(k);
       } 
      if( slx_type_in(h,k) == SELEX_5095LOGISTIC)           ///> logistic95 has 2 parameters
       { 
        nslx_rows_in += 2 * slx_nsel_period_in(k);
       }  
      if( slx_type_in(h,k) == SELEX_DECLLOGISTIC)           ///> declining logistic has 2 + extra parameters
       { 
        nslx_rows_in += (2+slx_extra_in(h,k)) * slx_nsel_period_in(k);
       }  
      if( slx_type_in(h,k) == SELEX_DOUBLENORM)             ///> double normal has 3 parameters
       {
        nslx_rows_in += 3 * slx_nsel_period_in(k);
       } 
      if( slx_type_in(h,k) == SELEX_DOUBLENORM4)            ///> double normal has 4 parameters
       {
        nslx_rows_in += 4 * slx_nsel_period_in(k);
       } 
      if( slx_type_in(h,k) == SELEX_UNIFORM1)               ///> uniform has 1 parameter
       {
        nslx_rows_in += 1 * slx_nsel_period_in(k);
       } 
      if( slx_type_in(h,k) == SELEX_UNIFORM0)               ///> uniform has 1 parameter
       {
        nslx_rows_in += 1 * slx_nsel_period_in(k);
       } 
      if( slx_type_in(h,k) == SELEX_CUBIC_SPLINE)          ///> spline has parameters for knots and values
       {
        nslx_rows_in += 2 * slx_extra_in(h,k) * slx_nsel_period_in(k);
       } 
      if( slx_type_in(h,k) <0)                            ///> mirror has 1 parameter
       {
        nslx_rows_in += 1 * slx_nsel_period_in(k);
       }
     }
    // Retention
    for ( int h = 1; h <= ret_bsex_in(k)+1; h++ )
     {
      if( ret_type_in(h,k) == SELEX_PARAMETRIC)             ///> parametric
       {
        nslx_rows_in += nclass * ret_nret_period_in(k);
       }  
      if( ret_type_in(h,k) == SELEX_COEFFICIENTS)           ///> coefficients
       {
         nslx_rows_in += ret_extra_in(h,k) * ret_nret_period_in(k);
       }  
      if( ret_type_in(h,k) == SELEX_STANLOGISTIC)           ///> logistic has 2 parameters
       {
        nslx_rows_in += 2 * ret_nret_period_in(k);
       } 
      if( ret_type_in(h,k) == SELEX_5095LOGISTIC)           ///> logistic95 has 2 parameters
       {
        nslx_rows_in += 2 * ret_nret_period_in(k);
       } 
      if( ret_type_in(h,k) == SELEX_DECLLOGISTIC)           ///> declining logistic has 2 + extra parameters
       { 
        nslx_rows_in += (2+ret_extra_in(h,k)) * ret_nret_period_in(k);
       }  
      if( ret_type_in(h,k) == SELEX_DOUBLENORM)             ///> double normal has 3 parameters
       {
        nslx_rows_in += 3 * ret_nret_period_in(k);
       } 
      if( ret_type_in(h,k) == SELEX_DOUBLENORM4)            ///> double normal has 4 parameters
       {
        nslx_rows_in += 4 * ret_nret_period_in(k);
       } 
      if( ret_type_in(h,k) == SELEX_UNIFORM1)               ///> uniform has 1 parameter
       {
        nslx_rows_in += 1 * ret_nret_period_in(k);
       } 
      if( ret_type_in(h,k) == SELEX_UNIFORM0)               ///> uniform has 1 parameter
       {
        nslx_rows_in += 1 * ret_nret_period_in(k);
       }
      if( ret_type_in(h,k) == SELEX_CUBIC_SPLINE)            ///> spline has parameters for knots and values
       {
        nslx_rows_in += 2 * ret_extra_in(h,k) * ret_nret_period_in(k);
       } 
      if( ret_type_in(h,k) <0)                             ///> mirror has 1 parameter
       {
        nslx_rows_in += 1 * ret_nret_period_in(k);
       }
     }
   }
  slx_control_in.allocate(1,nslx_rows_in,1,nslx_cols_in,"slx_control_in");
 gmacs_ctl  << "# Selectvity parameters" << endl;
 gmacs_ctl << "## Fleet: The index of the fleet  (positive for capture selectivity; negative for retention)" << endl;
 gmacs_ctl << "## Index: Parameter count (not used)" << endl;
 gmacs_ctl << "## Paramter_no: Parameter count within the current pattern (not used)" << endl;
 gmacs_ctl << "## Sex: Sex (not used)" << endl;
 gmacs_ctl << "## Initial: Initial value for the parameter (must lie between lower and upper)" << endl;
 gmacs_ctl << "## Lower & Upper: Range for the parameter" << endl;
 gmacs_ctl << "## Phase: Set equal to a negative number not to estimate" << endl;
 gmacs_ctl << "## Prior type:"  << endl;
 gmacs_ctl << "## 0: Uniform   - parameters are the range of the uniform prior"  << endl;
 gmacs_ctl << "## 1: Normal    - parameters are the mean and sd" << endl;
 gmacs_ctl << "## 2: Lognormal - parameters are the mean and sd of the log" << endl;
 gmacs_ctl << "## 3: Beta      - parameters are the two beta parameters [see dbeta]" << endl;
 gmacs_ctl << "## 4: Gamma     - parameters are the two gamma parameters [see dgamma]" << endl;
 gmacs_ctl << "## Start / End block: years to define the current block structure" << endl;
 gmacs_ctl << "# Fleet Index Parameter_no Sex Initial Lower_bound Upper_bound Phase Prior_type Prior_1 Prior_2 Start_block End_block" << endl;
 for (int k=1;k<=nslx_rows_in;k++)
  {
   if (slx_control_in(k,13) == nyr+1) 
    slx_control_in(k,13) = nyrRetro+1;
   else 
    if (slx_control_in(k,13) >= nyrRetro) 
     slx_control_in(k,13) = nyrRetro;
  }
 gmacs_ctl  << slx_control_in << endl;
  slx_control.allocate(1,nslx,1,nslx_cols_in);
  slx_indx.allocate(1,nslx);
  slx_gear.allocate(1,nslx);
  slx_type.allocate(1,nslx);
  slx_isex.allocate(1,nslx);
  slx_styr.allocate(1,nslx);
  slx_edyr.allocate(1,nslx);
  slx_cols.allocate(1,nslx);
  slx_npar.allocate(1,nslx);
  slx_incl.allocate(1,nslx);
  slx_extra.allocate(1,nslx);
  slx_max_at_1.allocate(1,nslx);
  // Work out the type of each selectivity and place in the ivector slx_type
  int kk = 1;
  for ( int k = 1; k <= nfleet; k++ )
   {
   int hh = 1 + slx_bsex_in(k);
   for ( int h = 1; h <= hh; h++ )
    for ( int i = 1; i <= slx_nsel_period_in(k); i++ )
      {
       slx_type(kk) = slx_type_in(h,k);
       slx_incl(kk) = slx_include_in(k);
       slx_extra(kk) = slx_extra_in(h,k);
       slx_max_at_1(kk) = slx_max_at_1_in(k);
       kk ++;
      }
    }
  for ( int k = 1; k <= nfleet; k++ )
   {
    int hh = 1 + ret_bsex_in(k);
    for ( int h = 1; h <= hh; h++ )
     for ( int i = 1; i <= ret_nret_period_in(k); i++ )
      {
       slx_type(kk) = ret_type_in(h,k);
       slx_extra(kk) = ret_extra_in(h,k);
	   slx_max_at_1(kk) = slx_max_at_1_in(k);
       kk ++;
      }
    }
  // count up number of parameters required
  slx_cols.initialize();
  slx_npar.initialize();
  for ( int k = 1; k <= nslx; k++ )
   {
    if ( slx_type(k) == SELEX_PARAMETRIC)                               ///> parametric
      { slx_cols(k) = nclass; slx_npar(k) = nclass; }
    if ( slx_type(k) == SELEX_COEFFICIENTS)                            ///> coefficients
      { slx_cols(k) = slx_extra(k); slx_npar(k) = slx_extra(k); }
    if ( slx_type(k) == SELEX_STANLOGISTIC)                            ///> logistic
      { slx_cols(k) = 2; slx_npar(k) = 2; }
    if ( slx_type(k) == SELEX_5095LOGISTIC)                            ///> logistic95
      { slx_cols(k) = 2; slx_npar(k) = 2; }
    if ( slx_type(k) == SELEX_DECLLOGISTIC)                            ///> declining logistic
      { slx_cols(k) = 2+slx_extra(k); slx_npar(k) = 2+slx_extra(k); }
    if ( slx_type(k) == SELEX_DOUBLENORM)                              ///> double normal
      { slx_cols(k) = 3; slx_npar(k) = 3; }
    if ( slx_type(k) == SELEX_DOUBLENORM4)                             ///> double normal4
      { slx_cols(k) = 4; slx_npar(k) = 4; }
    if ( slx_type(k) == SELEX_UNIFORM1)                                ///> constant 1
      { slx_cols(k) = 1;  slx_npar(k) = 1; }
    if ( slx_type(k) == SELEX_UNIFORM0)                                ///> constant 0
      { slx_cols(k) = 1; slx_npar(k) = 1; }
    if ( slx_type(k) == SELEX_CUBIC_SPLINE)                            ///> cubspline
      { slx_cols(k) = 2*slx_extra(k); slx_npar(k) = 2*slx_extra(k); }
    if ( slx_type(k) < 0)                                              ///> mirror
      { slx_cols(k) = 1; slx_npar(k) = 1; }
   }
  // slx_indx is an ivector of the index for the first parameter of each nslx in the slx_control_in matrix
  kk = 1;
  for ( int k = 1; k <= nslx; k++ )
   {
    slx_indx(k) = kk;
    kk += slx_cols(k);
   }
  // Store a version of the control file that only records the first parameter of each selectivity type - this is useful for R plots. Also extract vectors of elements from this matrix
  for ( int k = 1; k <= nslx; k++ )
   {
    int kk = slx_indx(k);
    for ( int i = 1; i <= nslx_cols_in; i++ )
     if (slx_cols(k) > 0)
      slx_control(k,i) = slx_control_in(kk,i);
    slx_gear(k) = slx_control_in(kk,1);
    slx_isex(k) = slx_control_in(kk,4);
    slx_styr(k) = slx_control_in(kk,12);
    slx_edyr(k) = slx_control_in(kk,13);
    if (slx_styr(k) < syr) 
     {
      cout << "Error: The end year selex block for fleet " << abs(slx_gear(k)) << " is before the start year" << endl;
      exit(1);
     }
    if (slx_edyr(k) > nyr+1) 
     {
      cout << "Error: The end year selex block for fleet " << abs(slx_gear(k)) << " is beyond the end year+1" << endl;
      exit(1);
     }
   }
  nslx_pars = sum(slx_cols);
  slx_par.allocate(1,nslx,1,slx_npar);
  slx_priors.allocate(1,nslx,1,slx_cols,1,3);
  slx_lb.allocate(1,nslx_pars);
  slx_ub.allocate(1,nslx_pars);
  slx_phzm.allocate(1,nslx_pars);
  for ( int k = 1; k <= nslx; k++ )
   //if (slx_type(k) >=0)
   {
    int kk = slx_indx(k);
    //cout << k << " " << kk << " " << slx_cols(k) << endl;
    for ( int j = 1; j <= slx_cols(k); j++ )               ///> read parameters for each pattern
     {
      int jj = kk + (j - 1);
      slx_par(k,j)      = slx_control_in(jj,5);            ///> init
      slx_priors(k,j,1) = slx_control_in(jj,8);            ///> prior type
      // If a uniform prior is specified then use the lb and ub rather than p1 and p2
      if ( slx_priors(k,j,1) == UNIFORM_PRIOR )
       {
        slx_priors(k,j,2) = slx_control_in(jj,6);          ///> p1
        slx_priors(k,j,3) = slx_control_in(jj,7);          ///> p2
       }
      else
       {
        slx_priors(k,j,2) = slx_control_in(jj,9);          ///> p1
        slx_priors(k,j,3) = slx_control_in(jj,10);         ///> p2
       }
      slx_phzm(jj) = slx_control_in(jj,11);
       if (slx_type(k) == 9 & slx_phzm(jj) != -999)
        {
         slx_lb(jj) = log(slx_control_in(jj,6)/(1.0-slx_control_in(jj,6)));
         slx_ub(jj) = log(slx_control_in(jj,7)/(1.0-slx_control_in(jj,7)));
        } 
       else
       {  
        slx_lb(jj) = log(slx_control_in(jj,6));
        slx_ub(jj) = log(slx_control_in(jj,7));
        }
      if (slx_type(k) == SELEX_UNIFORM1 || slx_type(k) == SELEX_UNIFORM0) slx_phzm(jj) = -1*abs(slx_phzm(jj));
     }
   }
  ECHO(slx_priors);
  log_slx_pars_init.allocate(1,nslx_pars);
  int jj = 1;                                              /// > Set the selectivity parameters
  for ( int k = 1; k <= nslx; k++ )
   for ( int i = 1; i <= slx_npar(k); i++ )
    if (slx_type(k) == 9 & slx_phzm(jj) != -999)
    { log_slx_pars_init(jj) = log(slx_par(k,i)/(1-slx_par(k,i))); jj++; }
    else
    { log_slx_pars_init(jj) = log(slx_par(k,i)); jj++; }
  NumAsympRet.allocate("NumAsympRet");
  AsympSel_control.allocate(1,NumAsympRet,1,7,"AsympSel_control");
  AsympSel_fleet.allocate(1,NumAsympRet);
  AsympSel_sex.allocate(1,NumAsympRet);
  AsympSel_year.allocate(1,NumAsympRet);
  AsympSel_ival.allocate(1,NumAsympRet);
  AsympSel_lb.allocate(1,NumAsympRet);
  AsympSel_ub.allocate(1,NumAsympRet);
  AsympSel_phz.allocate(1,NumAsympRet);
  gmacs_ctl << "#Number of asymptotic selectivity parameters" << endl;
  gmacs_ctl << NumAsympRet << endl;
  if (NumAsympRet > 0)
   {
    AsympSel_fleet = ivector(column(AsympSel_control,1));
    AsympSel_sex = ivector(column(AsympSel_control,2));
    AsympSel_year = ivector(column(AsympSel_control,3));
    AsympSel_ival = column(AsympSel_control,4);
    AsympSel_lb = column(AsympSel_control,5);
    AsympSel_ub = column(AsympSel_control,6);
    AsympSel_phz = ivector(column(AsympSel_control,7));
   }
  gmacs_ctl << "# Fleet Sex Year Initial lower_bound upper_bound phase" << endl;
  gmacs_ctl << AsympSel_control << endl;
 cout << " * Catchability parameter controls" << endl;
  q_controls.allocate(1,nSurveys,1,10,"q_controls");
  q_ival.allocate(1,nSurveys);
  q_lb.allocate(1,nSurveys);
  q_ub.allocate(1,nSurveys);
  q_phz.allocate(1,nSurveys);
  prior_qtype.allocate(1,nSurveys);
  prior_p1.allocate(1,nSurveys);
  prior_p2.allocate(1,nSurveys);
  q_anal.allocate(1,nSurveys);
  cpue_lambda.allocate(1,nSurveys);
  cpue_emphasis.allocate(1,nSurveys);
  gmacs_ctl << "#Catchability" << endl;
  gmacs_ctl << "# Initial Lower_bound Upper_bound Phase Prior_type Prior_1 Prior_2 Index_lambda Index_lambda" << endl;
  gmacs_ctl << q_controls << endl;
  q_ival        = column(q_controls,1);
  q_lb          = column(q_controls,2);
  q_ub          = column(q_controls,3);
  q_phz         = ivector(column(q_controls,4));
  prior_qtype   = ivector(column(q_controls,5));
  prior_p1      = column(q_controls,6);
  prior_p2      = column(q_controls,7);
  q_anal        = ivector(column(q_controls,8));
  cpue_lambda   = column(q_controls,9);
  cpue_emphasis = column(q_controls,10);
  for ( int k = 1; k <= nSurveys; k++ )
   {
    // If a uniform prior is specified then use the lb and ub rather than p1 and p2.
    if ( prior_qtype(k) == UNIFORM_PRIOR )
     {
      prior_p1(k) = q_lb(k);
      prior_p2(k) = q_ub(k);
     }
    if ( q_anal(k) == YES )
     {
      if ( prior_qtype(k) != UNIFORM_PRIOR || prior_qtype(k) != LOGNORMAL_PRIOR )
       {
        cout << "Error: you're only allowed to use a uniform or lognormal prior if the analytic q option is being used," << endl;
        cout << "       you can either specify a uniform or lognormal prior for q or switch analytic q off." << endl;
        exit(1);
       }
      // If we are using analytic q then turn off estimating this parameter by changing the estimation phase to be -ve.
      q_phz(k) = -1;
     }
   }
  ECHO(prior_qtype); ECHO(prior_p1); ECHO(prior_p2); ECHO(cpue_lambda);
 cout << " * Additional CV controls" << endl;
  cv_controls.allocate(1,nSurveys,1,7,"cv_controls");
 gmacs_ctl << "# Index CV" << endl;
 gmacs_ctl << "# Initial Lower_bound Upper_bound Phase Prior_type Prior_1 Prior_2" << endl;
 gmacs_ctl << cv_controls << endl;
  add_cv_ival.allocate(1,nSurveys);
  add_cv_lb.allocate(1,nSurveys);
  add_cv_ub.allocate(1,nSurveys);
  prior_add_cv_type.allocate(1,nSurveys);
  prior_add_cv_p1.allocate(1,nSurveys);
  prior_add_cv_p2.allocate(1,nSurveys);
  cv_phz.allocate(1,nSurveys);
  log_add_cv_ival.allocate(1,nSurveys);
  log_add_cv_lb.allocate(1,nSurveys);
  log_add_cv_ub.allocate(1,nSurveys);
  add_cv_ival       = column(cv_controls,1);
  add_cv_lb         = column(cv_controls,2);
  add_cv_ub         = column(cv_controls,3);
  cv_phz            = ivector(column(cv_controls,4));
  prior_add_cv_type = ivector(column(cv_controls,5));
  prior_add_cv_p1   = column(cv_controls,6);
  prior_add_cv_p2   = column(cv_controls,7);
  log_add_cv_ival   = log(add_cv_ival);
  log_add_cv_lb     = log(add_cv_lb);
  log_add_cv_ub     = log(add_cv_ub);
  for ( int k = 1; k <= nSurveys; k++ )
   {
    // If a uniform prior is specified then use the lb and ub rather than p1 and p2.
    if ( prior_add_cv_type(k) == UNIFORM_PRIOR )
     {
      prior_add_cv_p1(k) = add_cv_lb(k);
      prior_add_cv_p2(k) = add_cv_ub(k);
     }
   }
  ECHO(prior_add_cv_type); ECHO(prior_add_cv_p1); ECHO(prior_add_cv_p2);
 cout << " * Fishing mortality controls" << endl;
  f_controls.allocate(1,nfleet,1,12,"f_controls");
  f_phz.allocate(1,nfleet);
  foff_phz.allocate(1,nfleet);
  pen_fbar.allocate(1,nfleet);
  log_pen_fbar.allocate(1,nfleet);
  log_pen_fbar_foff.allocate(1,nfleet);
  pen_fstd.allocate(1,2,1,nfleet);
  fbar_lb.allocate(1,nfleet);
  fbar_ub.allocate(1,nfleet);
  fdev_lb.allocate(1,nfleet);
  fdev_ub.allocate(1,nfleet);
  foff_lb.allocate(1,nfleet);
  foff_ub.allocate(1,nfleet);
   gmacs_ctl << "# Controls on F" << endl;
   gmacs_ctl << "# Initial_male_f Initial_female_F Penalty_SD (early phase) Penalty_SD (later Phase) Phase_mean_F_male Phase_mean_F_female Lower_bound_mean_F Upper_bound_mean_F Lower_bound_annual_male_F Upper_bound_annual_male_F Lower_bound_annual_female_F Upper_bound_annual_female_F" << endl;
   gmacs_ctl << f_controls << endl;
   pen_fbar = column(f_controls,1);
   log_pen_fbar = log(pen_fbar + 1.0e-14);
   log_pen_fbar_foff = column(f_controls,2);
   log_pen_fbar_foff = log(log_pen_fbar_foff + 1.0e-14);
   for ( int i = 1; i <= 2; i++ ) pen_fstd(i) = trans(f_controls)(i+2);
   f_phz = ivector(column(f_controls,5));
   foff_phz = ivector(column(f_controls,6));
   ECHO(f_phz);
   ECHO(foff_phz);
   fbar_lb = column(f_controls,7);
   fbar_ub = column(f_controls,8);
   ECHO(fbar_lb);
   ECHO(fbar_ub);
   fdev_lb = column(f_controls,9);
   fdev_ub = column(f_controls,10);
   ECHO(fdev_lb);
   ECHO(fdev_ub);
   foff_lb = column(f_controls,11);
   foff_ub = column(f_controls,12);
   ECHO(foff_lb);
   ECHO(foff_ub);
 cout << " * Size composition controls" << endl;
  nAgeCompType_in.allocate(1,nSizeComps_in,"nAgeCompType_in");
 for (int k =1; k<=nSizeComps_in; k++)
  if (nAgeCompType_in(k) != 0 & nAgeCompType_in(k) != 1 & nAgeCompType_in(k) != 2 & nAgeCompType_in(k) != 5)
   { cout << "Size comp type must be 0, 1, 2 or 5" << endl; exit(1); }
  bTailCompression_in.allocate(1,nSizeComps_in,"bTailCompression_in");
  nvn_ival_in.allocate(1,nSizeComps_in,"nvn_ival_in");
  nvn_phz_in.allocate(1,nSizeComps_in,"nvn_phz_in");
  iCompAggregator.allocate(1,nSizeComps_in,"iCompAggregator");
  lf_lambda_in.allocate(1,nSizeComps_in,"lf_lambda_in");
  lf_emphasis_in.allocate(1,nSizeComps_in,"lf_emphasis_in");
 nSizeComps = max(iCompAggregator);                              ///> Number of length comps after compression
  nSizeCompRows.allocate(1,nSizeComps);
  nSizeCompCols.allocate(1,nSizeComps);
  nAgeCompType.allocate(1,nSizeComps);
  bTailCompression.allocate(1,nSizeComps);
  log_nvn_ival.allocate(1,nSizeComps);
  nvn_phz.allocate(1,nSizeComps);
  lf_lambda.allocate(1,nSizeComps);
  lf_emphasis.allocate(1,nSizeComps);
  gmacs_ctl <<"# Options when fitting size-composition data" << endl;
  gmacs_ctl << "## Likelihood types: " << endl;
  gmacs_ctl << "##  1:Multinomial with estimated/fixed sample size" << endl;
  gmacs_ctl << "##  2:Robust approximation to multinomial" << endl;
  gmacs_ctl << "##  3:logistic normal" << endl;
  gmacs_ctl << "##  4:multivariate-t" << endl;
  gmacs_ctl << "##  5:Dirichlet" << endl;
  gmacs_ctl << endl;
  anystring = "# ";
  for ( int kk = 1; kk <= nSizeComps_in; kk++ ) anystring = anystring + " " + fleetname(d3_SizeComps_in(kk,1,-5));
  gmacs_ctl << anystring << endl;
  anystring = "# ";
  for ( int kk = 1; kk <= nSizeComps_in; kk++ )
   {
    if (d3_SizeComps_in(kk,1,-4)==BOTHSEX)          anystring = anystring +" male+female";
    if (d3_SizeComps_in(kk,1,-4)==MALESANDCOMBINED) anystring = anystring +" male";
    if (d3_SizeComps_in(kk,1,-4)==FEMALES)          anystring = anystring +" female";
   }
  gmacs_ctl << anystring << endl;
  anystring = "# ";
  for ( int kk = 1; kk <= nSizeComps_in; kk++ )
   {
    if (d3_SizeComps_in(kk,1,-3)==TOTALCATCH)       anystring = anystring +" total";
    if (d3_SizeComps_in(kk,1,-3)==RETAINED)         anystring = anystring +" retained";
    if (d3_SizeComps_in(kk,1,-3)==DISCARDED)        anystring = anystring +" discard";
   } 
  gmacs_ctl << anystring << endl;
  anystring = "# ";
  for ( int kk = 1; kk <= nSizeComps_in; kk++ )
   {
    if (d3_SizeComps_in(kk,1,-2)==UNDET_SHELL)      anystring = anystring +" all_shell";
    if (d3_SizeComps_in(kk,1,-2)==NEW_SHELL)        anystring = anystring +" newshell";
    if (d3_SizeComps_in(kk,1,-2)==OLD_SHELL)        anystring = anystring +" oldshell";
   } 
  gmacs_ctl << anystring << endl;
  anystring = "# ";
  for ( int kk = 1; kk <= nSizeComps_in; kk++ )
   {
    if (d3_SizeComps_in(kk,1,-1)==BOTHMATURE)       anystring = anystring +" immature+mature";
    if (d3_SizeComps_in(kk,1,-1)==IMMATURE)         anystring = anystring +" immature";
    if (d3_SizeComps_in(kk,1,-1)==MATURE)           anystring = anystring +" mature";    
   }
  gmacs_ctl << anystring << endl;
  
  gmacs_ctl << nAgeCompType_in << " # Type of likelihood" <<  endl;
  gmacs_ctl << bTailCompression_in << " # Auto tail compression (pmin)" <<  endl;
  gmacs_ctl << nvn_ival_in << " # Initial value for effective sample size multiplier" << endl;
  gmacs_ctl << nvn_phz_in << " # Phz for estimating effective sample size (if appl.)" << endl;
  gmacs_ctl << iCompAggregator << " # Composition appender" << endl;
  gmacs_ctl << lf_lambda_in << " # Lambda for effective sample size" << endl;
  gmacs_ctl << lf_emphasis_in << " # Lambda for overall likelihood" << endl;
  nSizeCompCols.initialize();
  for ( int kk = 1; kk <= nSizeComps_in; kk++ )
   {
    int k = iCompAggregator(kk);
    // Currently this only works if the number of rows in each size composition group are the same and have the same years. If not then gmacs throws an error.
    nSizeCompRows(k) = nSizeCompRows_in(kk);
    // We are appending the arrays horizontally.
    nSizeCompCols(k) += nSizeCompCols_in(kk);
    // Again, we are using only the last specification here, may want to add a check to ensure the user specifies that these are the same and throw an error if not.
    nAgeCompType(k) = nAgeCompType_in(kk);
    bTailCompression(k) = bTailCompression_in(kk);
    log_nvn_ival(k) = log(nvn_ival_in(kk));
    nvn_phz(k) = nvn_phz_in(kk);
    lf_lambda(k) = lf_lambda_in(kk);
    lf_emphasis(k) = lf_emphasis_in(kk);
   }
  // Do the checks mentioned above
  for ( int kk = 1; kk <= nSizeComps_in; kk++ )
   {
    int k = iCompAggregator(kk);
    if ( nSizeCompRows(k) != nSizeCompRows_in(kk) )
     {
      cout << "Error: dimension mismatch in size-compositions being aggregated " << kk << " " << k << " " << nSizeCompRows_in(kk) << " "<<  nSizeCompRows(k) << endl;
      exit(1);
     }
    if ( nAgeCompType(k) != nAgeCompType_in(kk) )
     {
      cout << "Error: mismatch in type of likelihood for size-compositions being aggregated" << endl;
      exit(1);
     }
    if ( bTailCompression(k) != bTailCompression_in(kk) )
     {
      cout << "Error: mismatch in auto tail compression for size-compositions being aggregated" << endl;
      exit(1);
     }
    if ( log_nvn_ival(k) != log(nvn_ival_in(kk)) )
     {
      cout << "Error: mismatch in initial value of effective sample size for size-compositions being aggregated" << endl;
      exit(1);
     }
    if ( nvn_phz(k) != nvn_phz_in(kk) )
     {
      cout << "Error: mismatch in phase for estimation of effective sample size for size-compositions being aggregated" << endl;
      exit(1);
     }
   }
  int rowCount;
  // This aggregates the size composition data by appending size comps horizontally
  for ( int kk = 1; kk <= nSizeComps_in; kk++ )
   {
    int k = iCompAggregator(kk);
    rowCount = 0;
    for ( int ii = 1; ii <= nSizeCompRows_in(kk); ii++ )
     if (d3_SizeComps_in(kk,ii,-7) <= nyrRetro || (d3_SizeComps_in(kk,ii,-7) == nyrRetro+1 & d3_SizeComps_in(kk,ii,-6) == 1) ) rowCount += 1;
    nSizeCompRows(k) = rowCount;
   }
  d3_obs_size_comps.allocate(1,nSizeComps,1,nSizeCompRows,1,nSizeCompCols);
  size_comp_sample_size.allocate(1,nSizeComps,1,nSizeCompRows);
  size_comp_year.allocate(1,nSizeComps,1,nSizeCompRows);
  size_comp_season.allocate(1,nSizeComps,1,nSizeCompRows);
  ilike_vector.allocate(1,nlikes);
  int i,j;
  int oldk = 9999;
  // This aggregates the size composition data by appending size comps horizontally
  for ( int kk = 1; kk <= nSizeComps_in; kk++ )
   {
    int k = iCompAggregator(kk);
    if ( oldk != k ) j = 0;
    oldk = k;
    for ( int jj = 1; jj <= nSizeCompCols_in(kk); jj++ )
     {
      j += 1;
      for ( int ii = 1; ii <= nSizeCompRows_in(kk); ii++ )
       if (d3_SizeComps_in(kk,ii,-7) <= nyrRetro || (d3_SizeComps_in(kk,ii,-7) == nyrRetro+1 & d3_SizeComps_in(kk,ii,-6) == 1) )
       { i = ii; d3_obs_size_comps(k,i,j) = d3_obs_size_comps_in(kk,i,jj); }
     }
   }
   
  // The size composition sample sizes are calculated as the sum of the aggregated sample sizes
  size_comp_sample_size.initialize();
  for ( int kk = 1; kk <= nSizeComps_in; kk++ )
   {
    int k = iCompAggregator(kk);
    for ( int ii = 1; ii <= nSizeCompRows_in(kk); ii++ )
     if (d3_SizeComps_in(kk,ii,-7) <= nyrRetro || (d3_SizeComps_in(kk,ii,-7) == nyrRetro+1 & d3_SizeComps_in(kk,ii,-6) == 1) )
      {
       size_comp_sample_size(k,ii) += size_comp_sample_size_in(kk,ii);
       size_comp_year(k,ii) = size_comp_year_in(kk,ii);
       size_comp_season(k,ii) = size_comp_season_in(kk,ii);
      } 
   }
  for ( int kk = 1; kk <= nSizeComps_in; kk++ )
   {
    int k = iCompAggregator(kk);
    for ( int ii = 1; ii <= nSizeCompRows_in(kk); ii++ )
     if (d3_SizeComps_in(kk,ii,-7) <= nyrRetro || (d3_SizeComps_in(kk,ii,-7) == nyrRetro+1 & d3_SizeComps_in(kk,ii,-6) == 1) )
      {
       if ( size_comp_year(k,ii) != size_comp_year_in(kk,ii) )
        {
         cout << "Error: mismatch in years for size-compositions being aggregated" << endl;
         cout << "       see the " << size_comp_year_in(kk,ii) << " year in size composition " << kk << " in the .dat file" << endl;
          exit(1);
        }
      }
   }
  // This normalizes all observations by row
  for ( int k = 1; k <= nSizeComps; k++ )
   for ( int i = 1; i <= nSizeCompRows(k); i++ )
    if (size_comp_year(k,i) <= nyrRetro || (size_comp_year(k,i) == nyrRetro+1 & size_comp_season(k,i) == 1) )
     d3_obs_size_comps(k,i) /= sum(d3_obs_size_comps(k,i));
     
  ECHO(d3_obs_size_comps);
  ilike_vector(1) = nCatchDF;
  like_names      =  adstring("Catch ");
  ilike_vector(2) = nSurveys;
  like_names      = like_names + adstring("Survey_Indices ");
  ilike_vector(3) = nSizeComps;
  like_names      = like_names + adstring("SizeComps ");
  ilike_vector(4) = 3;
  ilike_vector(5) = nsex;
 cout << " * Natural mortality controls" << endl;
 gmacs_ctl << "# Type of M specification" << endl;
 gmacs_ctl << "## 1: Time-invariant M" << endl;
 gmacs_ctl << "## 2: Default random walk M" << endl;
 gmacs_ctl << "## 3: Cubic spline with time M" << endl;
 gmacs_ctl << "## 4: Blocked changes in  M" << endl;
 gmacs_ctl << "## 5: Blocked changes in  M (type 2)" << endl;
 gmacs_ctl << "## 6: Blocked changes in  M (returns to default)" << endl;
  m_type.allocate("m_type");
 WriteCtl(m_type);
 if (nsex>1)
  {
   *(ad_comm::global_datafile) >> MrelFem;
   if (MrelFem != YES & MrelFem != NO)
    { cout << "MrelFem can only be 0[No; absolute] or 1[Relative]; STOPPING" << endl; exit(1); }
  }
  Mdev_phz_def.allocate("Mdev_phz_def");
  m_stdev.allocate("m_stdev");
  m_nNodes_sex.allocate(1,nsex,"m_nNodes_sex");
  m_nodeyear_sex.allocate(1,nsex,1,m_nNodes_sex,"m_nodeyear_sex");
  nSizeDevs.allocate("nSizeDevs");
  m_size_nodeyear.allocate(1,nSizeDevs,"m_size_nodeyear");
  Init_Mdev.allocate("Init_Mdev");
  nMdev_par_cnt.allocate(1,nsex);
  
  if (nsex > 1)  gmacs_ctl << "# How does M for females relate to that for males (0 absolute; 1 relative)"<< endl << MrelFem << endl;
  WriteCtl(Mdev_phz_def);
  WriteCtl(m_stdev);
  WriteCtl(m_nNodes_sex);
  gmacs_ctl << "# Start of the blocks in which M changes (one row for each sex) - the first block starts in " << syr << endl;
  gmacs_ctl << "# Note: there is one less year than there are blocks" << endl;
  for (int isex=1;isex<=nsex;isex++)
   gmacs_ctl << m_nodeyear_sex(isex) << " # " << sexes(isex)  << endl;
  WriteCtl(nSizeDevs);
  gmacs_ctl << "# Start of the size-class blocks in which M changes (one row for each sex) - the first block start at size-class 1" << endl;
  gmacs_ctl << "# Note: there is one less size-class than there are blocks (no input implies M is independent of size" << endl;
  gmacs_ctl << m_size_nodeyear << endl;
  WriteCtl(Init_Mdev);
  nMdev_par_cnt.initialize();
  switch ( m_type )
   {
    case M_CONSTANT:
     nMdev = 0;
     Mdev_phz_def = -1;
     break;
    case M_RANDOM:
     nMdev = nsex*(nyr - syr);
     nMdev_par_cnt(1) = (nyr - syr);
     if (nsex > 0) nMdev_par_cnt(2) = (nyr - syr);
     break;
    case M_CUBIC_SPLINE:
     nMdev = sum(m_nNodes_sex);
     nMdev_par_cnt(1) =  m_nNodes_sex(1);
     if (nsex>1) nMdev_par_cnt(2) = m_nNodes_sex(2);
     break;
    case M_BLOCKED_CHANGES:
     nMdev = sum(m_nNodes_sex);
     nMdev_par_cnt(1) =  m_nNodes_sex(1);
     if (nsex>1) nMdev_par_cnt(2) = m_nNodes_sex(2);
     break;
    case M_TIME_BLOCKS1:                 //added by Jie Zheng
     nMdev = sum(m_nNodes_sex)/2;
     nMdev_par_cnt(1) =  m_nNodes_sex(1)/2;
     if (nsex>1) nMdev_par_cnt(2) = m_nNodes_sex(2)/2;
     break;
    case M_TIME_BLOCKS2:
     nMdev = sum(m_nNodes_sex);
     nMdev_par_cnt(1) =  m_nNodes_sex(1);
     if (nsex>1) nMdev_par_cnt(2) = m_nNodes_sex(2);
     break;
   }
 nMdev += nSizeDevs;
  Mdev_ival.allocate(1,nMdev);
  Mdev_lb.allocate(1,nMdev);
  Mdev_ub.allocate(1,nMdev);
  Mdev_phz.allocate(1,nMdev);
  Mdev_spec.allocate(1,nMdev);
  if (Init_Mdev==YES)
   {
    for (int I = 1; I <=nMdev; I++)
     {
      *(ad_comm::global_datafile) >> Mdev_ival(I) >> Mdev_lb(I)>> Mdev_ub(I) >> Mdev_phz(I)  >> Mdev_spec(I);
      gmacs_ctl << "# " << "#Mparameters" << "\n" << " " << Mdev_ival(I) << " " << Mdev_lb(I) << " " << Mdev_ub(I) << " " << Mdev_phz(I)  << " " << Mdev_spec(I) << endl;
      if (Mdev_spec(I) < 0) Mdev_phz(I) = -1;
     }
   }
  else
   {
    for (int I = 1; I <=nMdev; I++)
    { Mdev_ival(I) = 0; Mdev_lb(I) = -3; Mdev_ub(I) = 3; Mdev_phz(I) = Mdev_phz_def; }
   }
 cout << " * Immature/mature M controls" << endl;
  m_maturity.allocate("m_maturity");
 n_mat_m = nsex;
  m_mat_controls.allocate(1,nsex,1,7,"m_mat_controls");
 gmacs_ctl << "# maturity M" << endl;
 gmacs_ctl << "# Initial Lower_bound Upper_bound Phase Prior_type Prior_1 Prior_2" << endl;
 gmacs_ctl << m_mat_controls << endl;
  m_mat_ival.allocate(1,nsex);
  m_mat_lb.allocate(1,nsex);
  m_mat_ub.allocate(1,nsex);
  prior_m_mat_type.allocate(1,nsex);
  prior_m_mat_p1.allocate(1,nsex);
  prior_m_mat_p2.allocate(1,nsex);
  m_mat_phz.allocate(1,nsex);
  log_m_mat_ival.allocate(1,nsex);
  log_m_mat_lb.allocate(1,nsex);
  log_am_mat_ub.allocate(1,nsex);
  m_mat_ival       = column(m_mat_controls,1);
  m_mat_lb         = column(m_mat_controls,2);
  m_mat_ub         = column(m_mat_controls,3);
  m_mat_phz        = ivector(column(m_mat_controls,4));
  prior_m_mat_type = ivector(column(m_mat_controls,5));
  prior_m_mat_p1   = column(m_mat_controls,6);
  prior_m_mat_p2   = column(m_mat_controls,7);
  for ( int k = 1; k <= nsex; k++ )
   {
    // If a uniform prior is specified then use the lb and ub rather than p1 and p2.
    if ( prior_m_mat_type(k) == UNIFORM_PRIOR )
     {
      prior_m_mat_p1(k) = m_mat_lb(k);
      prior_m_mat_p2(k) = m_mat_ub(k);
     }
   }
  ECHO(prior_m_mat_type); ECHO(prior_m_mat_p1); ECHO(prior_m_mat_p2);
 cout << " * Other controls" << endl;
  model_controls.allocate(1,12,"model_controls");
  rdv_syr             = int(model_controls(1));
  if ( rdv_syr < syr )
   {
     cout << "Error: recruitment cannot be estimated before start year" << endl;
     exit(1);
   }
  model_controls(2) -= (nyr-nyrRetro);
  rdv_eyr             = int(model_controls(2));
  if ( rdv_eyr < rdv_syr )
   {
     cout << "Error: end recruitment year must be before start recruitment year" << endl;
     exit(1);
   }
  if ( rdv_eyr > nyr )
   {
     cout << "Error: recruitment cannot be estimated after end year" << endl;
     exit(1);
   }
  rdv_phz             = int(model_controls(3));
  if (nsex==1) rec_prop_phz = -1; else rec_prop_phz = int(model_controls(4));
  init_sex_ratio = model_controls(5);
  init_sex_ratio = -1.0*log((1.0-init_sex_ratio)/init_sex_ratio);
  
  rec_ini_phz         = int(model_controls(6));
  verbose             = int(model_controls(7));
  bInitializeUnfished = int(model_controls(8));
  spr_lambda          = model_controls(9);
  nSRR_flag           = int(model_controls(10));
  TurnOffPhase        = int(model_controls(11));
  StopAfterFnCall     = int(model_controls(12));
  gmacs_ctl << endl << "# Extra controls" << endl;
  gmacs_ctl << model_controls(1) << " # First year of recruitment estimation" << endl;
  gmacs_ctl << model_controls(2) << " # Last year of recruitment estimation" << endl;
  gmacs_ctl << model_controls(3) << " # Phase for recruitment estimation" << endl;
  gmacs_ctl << model_controls(4) << " # Phase for recruitment sex-ratio estimation" << endl;
  gmacs_ctl << model_controls(5) << " # Initial value for recruitment sex-ratio" << endl;
  gmacs_ctl << model_controls(6) << " # Phase for initial recruitment estimation" << endl;
  gmacs_ctl << model_controls(7) << " # VERBOSE FLAG (0 = off, 1 = on, 2 = objective func; 3 diagnostics)" << endl;
  gmacs_ctl << model_controls(8) << " # Initial conditions (0 = Unfished, 1 = Steady-state fished, 2 = Free parameters, 3 = Free parameters (revised))" << endl;
  gmacs_ctl << model_controls(9) << " # Lambda (proportion of mature male biomass for SPR reference points)" << endl;
  gmacs_ctl << model_controls(10) << " # Stock-Recruit-Relationship (0 = none, 1 = Beverton-Holt)" << endl;
  gmacs_ctl << model_controls(11) << " # Maximum phase (stop the estimation after this phase)" << endl;
  gmacs_ctl << model_controls(12) << " # Maximum number of function calls" << endl;
  gmacs_ctl << endl;
  // Some combinations of options don't work
  if ( bInitializeUnfished == UNFISHEDEQN & theta_phz(nsex+2) > 0 )
   { cout << "Error: cannot LogRini when unfished steady state is selected" << endl;  exit(1); }
  if ( bInitializeUnfished == FISHEDEQN & theta_phz(nsex+1) > 0 )
   { cout << "Error: cannot LogR0 when fished steady state is selected" << endl;  exit(1); }
  if ( bInitializeUnfished == FREEPARS && theta_phz(nsex+1) > 0 )
   {
     cout << "Error: cannot estimate LogR0 when individual parameters are estimated" << endl;
     exit(1);
   }
  if ( bInitializeUnfished == FREEPARS && theta_phz(nsex+2) > 0 )
   {
     cout << "Error: cannot estimate LogRini when individual parameters are estimated" << endl;
     exit(1);
   }
  if ( (bInitializeUnfished == FREEPARS || bInitializeUnfished == FREEPARSSCALED) && rec_ini_phz > 0 )
   {
     cout << "Error: cannot estimate initial rec_devs for free parameters" << endl;
     exit(1);
   }
  // Default number of parameters
  nthetatest = nsex+3 + 2*nsex + 3;
  if (bInitializeUnfished == FISHEDEQN) nthetatest += nfleet;
  if (bInitializeUnfished == FREEPARS) nthetatest += nclass*nsex*nmature*nshell;
  if (bInitializeUnfished == FREEPARSSCALED) nthetatest += (nclass*nsex*nmature*nshell-1);
  if (nthetatest != ntheta)
   {
    cout << "Error: the specified number of theta parameters does not match the expected value of " << nthetatest << endl;
    exit(1);
   }
  catch_emphasis.allocate(1,nCatchDF,"catch_emphasis");
 WriteCtl(catch_emphasis);
  Penalty_emphasis.allocate(1,9,"Penalty_emphasis");
 WriteCtl(Penalty_emphasis);
  eof_ctl.allocate("eof_ctl");
 WriteCtl(eof_ctl);
 if ( eof_ctl != 9999 ){cout << "Error reading control file" << endl; exit(1);}
 cout << "end of control section" << endl;
 ad_comm::change_datafile_name(projectfile);
 cout << "+-------------------------+" << endl;
 cout << "| Reading projection file |" << endl;
 cout << "+-------------------------+" << endl;
  Calc_MSY.allocate("Calc_MSY");
 WRITEPRJ(Calc_MSY);
 if (Calc_MSY != NO && Calc_MSY != YES)  { cout << "Indicate 1=Yes or 0=No for whether MSY should be computed" << endl; exit(1); }
  Ffixed.allocate(1,nfleet,"Ffixed");
 WRITEPRJ(Ffixed);
 for (int k=1;k<=nfleet;k++)
  if (Ffixed(k) != NO & Ffixed(k) != YES) { cout << "Future F indicator must be 0 or 1" << endl; exit(1); }
  spr_syr.allocate("spr_syr");
 WRITEPRJ(spr_syr);
 if (spr_syr < syr) { cout << "First year for computing Rbar must be syr or later: STOPPING" << endl; exit(1); }
  spr_nyr.allocate("spr_nyr");
 WRITEPRJ(spr_nyr);
 if (spr_nyr > nyr) { cout << "Last year for computing Rbar must be nyr or earlier: STOPPING" << endl; exit(1); }
 if( spr_nyr < spr_syr)  { cout << "Last year for computing Rbar must be later than the first year" << endl; exit(1); }
  SexR_syr.allocate("SexR_syr");
 WRITEPRJ(SexR_syr);
 if (SexR_syr < syr) { cout << "First year for computing sex ratio must be syr or later: STOPPING" << endl; exit(1); }
  SexR_nyr.allocate("SexR_nyr");
 WRITEPRJ(SexR_nyr);
 if (SexR_nyr > nyr) { cout << "Last year for computing sex ratio must be nyr or earlier: STOPPING" << endl; exit(1); }
 if( SexR_nyr < SexR_syr)  { cout << "Last year for computing sex ratio must be later than the first year" << endl; exit(1); }
  spr_aveF_syr.allocate("spr_aveF_syr");
 WRITEPRJ(spr_aveF_syr);
 if (spr_aveF_syr < syr) { cout << "First year for computing AveF must be syr or later: STOPPING" << endl; exit(1); }
  spr_aveF_nyr.allocate("spr_aveF_nyr");
 WRITEPRJ(spr_aveF_nyr);
 if (spr_aveF_nyr > nyr) { cout << "Last year for computing AveF must be nyr or earlier: STOPPING" << endl; exit(1); }
 if( spr_aveF_nyr < spr_aveF_syr)  { cout << "Last year for computing AveF must be later than the first year" << endl; exit(1); }
  spr_target.allocate("spr_target");
 WRITEPRJ(spr_target);
  OFLTier.allocate("OFLTier");
 WRITEPRJ(OFLTier);
  OFLalpha.allocate("OFLalpha");
 WRITEPRJ(OFLalpha);
  OFLbeta.allocate("OFLbeta");
 WRITEPRJ(OFLbeta);
  OFLgamma.allocate("OFLgamma");
 WRITEPRJ(OFLgamma);
  ABCBuffer.allocate("ABCBuffer");
 WRITEPRJ(ABCBuffer);
  Compute_yield_prj.allocate("Compute_yield_prj");
 if (Compute_yield_prj != NO & Compute_yield_prj != YES)  { cout << "Indicate 1=Yes or 0=No for whether the yield function should be reported" << endl; exit(1); }
 if (Calc_MSY==NO) Compute_yield_prj = NO;
 WRITEPRJ(Compute_yield_prj);
  pyr.allocate("pyr");
 WRITEPRJ(pyr);
  prj_Nstrat.allocate("prj_Nstrat");
 WRITEPRJ(prj_Nstrat);
  nproj = pyr - nyr;
 if (nproj < 0) { cout << "Terminal year for project must be later tha nyr: STOPPING" << endl; exit(1); }
  prj_lowF.allocate("prj_lowF");
 WRITEPRJ(prj_lowF);
  prj_hiF.allocate("prj_hiF");
 WRITEPRJ(prj_hiF);
  prj_bycatch_on.allocate("prj_bycatch_on");
 WRITEPRJ(prj_bycatch_on);
  prj_replicates.allocate("prj_replicates");
 WRITEPRJ(prj_replicates);
  Fixed_prj_Bmsy.allocate("Fixed_prj_Bmsy");
 WRITEPRJ(Fixed_prj_Bmsy);
  Stock_rec_prj.allocate("Stock_rec_prj");
 WRITEPRJ(Stock_rec_prj);
  Age_at_rec_prj.allocate("Age_at_rec_prj");
 WRITEPRJ(Age_at_rec_prj);
  prj_futRec_syr.allocate("prj_futRec_syr");
 WRITEPRJ(prj_futRec_syr);
 if (prj_futRec_syr < syr) { cout << "First year for generating recruitment must be syr or later: STOPPING" << endl; exit(1); }
  prj_futRec_nyr.allocate("prj_futRec_nyr");
 WRITEPRJ(prj_futRec_nyr);
 if (prj_futRec_nyr > nyr) { cout << "Last year for generating recruitment must be nyr or earlier: STOPPING" << endl; exit(1); }
 if(prj_futRec_nyr < prj_futRec_syr)  { cout << "Last year for generating recruitment must be later than the first year" << endl; exit(1); }
  mean_rec_prj.allocate("mean_rec_prj");
 WRITEPRJ(mean_rec_prj);
  SigmaR_prj.allocate("SigmaR_prj");
 WRITEPRJ(SigmaR_prj);
  Prow_prj.allocate("Prow_prj");
 WRITEPRJ(Prow_prj);
  Initial_eps.allocate("Initial_eps");
 WRITEPRJ(Initial_eps);
  Apply_HCR_prj.allocate("Apply_HCR_prj");
 WRITEPRJ(Apply_HCR_prj);
  MeanWStateMature.allocate("MeanWStateMature");
 WRITEPRJ(MeanWStateMature);
  MeanWStateLegal.allocate("MeanWStateLegal");
 WRITEPRJ(MeanWStateLegal);
  max_prj.allocate("max_prj");
 WRITEPRJ(max_prj);
  eof_prj.allocate("eof_prj");
 WRITEPRJ(eof_prj);
 if ( eof_prj != 9999 ){cout << "Error reading projection file: " << eof_prj << endl; exit(1);}
 cout << "end of projection section" << endl;
  xg.allocate(1,32);
  wg.allocate(1,32);
  l1_vec.allocate(1,nsex,1,nclass,1,32);
  NVarPar = 0;
  int Ipar;
  for (Ipar=1;Ipar<=ntheta; Ipar++) if (theta_phz(Ipar) > TurnOffPhase) theta_phz(Ipar) = -1;
  for (Ipar=1;Ipar<=nGrwth; Ipar++) if (Grwth_phz(Ipar) > TurnOffPhase) Grwth_phz(Ipar) = -1;
  for (Ipar=1;Ipar<=nslx_pars; Ipar++) if (slx_phzm(Ipar) > TurnOffPhase) slx_phzm(Ipar) = -1;
  for (Ipar=1;Ipar<=NumAsympRet; Ipar++) if (AsympSel_phz(Ipar) > TurnOffPhase) AsympSel_phz(Ipar) = -1;
  for (Ipar=1;Ipar<=nfleet; Ipar++) if (f_phz(Ipar) > TurnOffPhase) f_phz(Ipar) = -1;
  for (Ipar=1;Ipar<=nfleet; Ipar++) if (foff_phz(Ipar) > TurnOffPhase) foff_phz(Ipar) = -1;
  if (rec_ini_phz > TurnOffPhase) rec_ini_phz = -1;
  if (rdv_phz > TurnOffPhase) rdv_phz = -1;
  if (rec_prop_phz > TurnOffPhase) rec_prop_phz = -1;
  for (Ipar=1;Ipar<=nMdev; Ipar++) if (Mdev_phz(Ipar) > TurnOffPhase) Mdev_phz(Ipar) = -1;
  for (Ipar=1;Ipar<=nSizeComps; Ipar++) if (nvn_phz(Ipar) > TurnOffPhase) nvn_phz(Ipar) = -1;
  for (Ipar=1;Ipar<=nSurveys; Ipar++) if (q_phz(Ipar) > TurnOffPhase) q_phz(Ipar) = -1;
  for (Ipar=1;Ipar<=nSurveys; Ipar++) if (cv_phz(Ipar) > TurnOffPhase) cv_phz(Ipar) = -1;
  for (Ipar=1;Ipar<=ntheta; Ipar++) if (theta_phz(Ipar) > 0) NVarPar += 1;
  for (Ipar=1;Ipar<=nGrwth; Ipar++) if (Grwth_phz(Ipar) > 0) NVarPar += 1;
  for (Ipar=1;Ipar<=nslx_pars; Ipar++) if (slx_phzm(Ipar) > 0) NVarPar += 1;
  for (Ipar=1;Ipar<=NumAsympRet; Ipar++) if (AsympSel_phz(Ipar) > 0) NVarPar += 1;
  for (Ipar=1;Ipar<=nfleet; Ipar++) if (f_phz(Ipar) > 0) NVarPar += 1;
  for (Ipar=1;Ipar<=nfleet; Ipar++) if (f_phz(Ipar) > 0) NVarPar += nFparams(Ipar);
  for (Ipar=1;Ipar<=nfleet; Ipar++) if (foff_phz(Ipar) > 0) NVarPar += 1;
  for (Ipar=1;Ipar<=nfleet; Ipar++) if (foff_phz(Ipar) > 0) NVarPar += nYparams(Ipar);
  if (rec_ini_phz > 0) NVarPar += nclass;
  if (rdv_phz > 0) NVarPar += (rdv_eyr-rdv_syr+1);
  if (rec_prop_phz > 0) NVarPar += (rdv_eyr-rdv_syr+1);
  for (Ipar=1;Ipar<=nMdev; Ipar++) if (Mdev_phz(Ipar) > 0) NVarPar += 1;
  for (Ipar=1;Ipar<=n_mat_m; Ipar++) if (m_mat_phz(Ipar) > 0) NVarPar += 1;
  for (Ipar=1;Ipar<=nSizeComps; Ipar++) if (nvn_phz(Ipar) > 0) NVarPar += 1;
  for (Ipar=1;Ipar<=nSurveys; Ipar++) if (q_phz(Ipar) > 0) NVarPar += 1;
  for (Ipar=1;Ipar<=nSurveys; Ipar++) if (cv_phz(Ipar) > 0) NVarPar += 1;
  PhaseGrowthPar = 10000;                                  ///> Lowest phase for a growth parameter
  for (Ipar=1;Ipar<=nGrwth; Ipar++) if (Grwth_phz(Ipar) > 0 & Grwth_phz(Ipar) < PhaseGrowthPar) PhaseGrowthPar = Grwth_phz(Ipar);
  PhaseSelexPar = 10000;
  for (Ipar=1;Ipar<=nslx; Ipar++) if (slx_phzm(Ipar) > 0 & slx_phzm(Ipar) < PhaseSelexPar) PhaseSelexPar = slx_phzm(Ipar);
  for (Ipar=1;Ipar<=NumAsympRet; Ipar++) if (AsympSel_phz(Ipar) > 0 & AsympSel_phz(Ipar) < PhaseSelexPar) PhaseSelexPar = AsympSel_phz(Ipar);
 NfunCall = 0;
}

void model_parameters::initializationfunction(void)
{
  theta.set_initial_value(theta_ival);
  Grwth.set_initial_value(Grwth_ival);
  Asymret.set_initial_value(AsympSel_ival);
  log_fbar.set_initial_value(log_pen_fbar);
  log_vn.set_initial_value(log_nvn_ival);
  survey_q.set_initial_value(q_ival);
  logit_rec_prop_est.set_initial_value(init_sex_ratio);
  log_add_cv.set_initial_value(log_add_cv_ival);
  m_dev_est.set_initial_value(Mdev_ival);
  log_slx_pars.set_initial_value(log_slx_pars_init);
}

model_parameters::model_parameters(int sz,int argc,char * argv[]) : 
 model_data(argc,argv) , function_minimizer(sz)
{
  initializationfunction();
 cout << "+----------------------+" << endl;
 cout << "| Parameter section    |" << endl;
 cout << "+----------------------+" << endl;
  if (0){
     //Testing selectivity using "dvar" values
    cout<<"|-----------------------------------|"<<endl;
    cout<<"| Testing sandbox using dvar values |"<<endl;
    cout<<"|-----------------------------------|"<<endl;
    class gsm::Selex<dvar_vector> *pSLX;      
    dvar_vector z(1,32);
    for (int i=z.indexmin();i<=z.indexmax();i++) z(i) = 27.5+(i-1)*5.0;
    cout<<"--Cubic Spline"<<endl;
    dvar_vector x_knts(1,5);
    x_knts[1]=z[1]; for (int i=1;i<=4;i++) x_knts[i+1] = z[8*i];
    dvar_vector y_vals = 1.0/(1.0+exp(-(x_knts-100.0)/30.0));
    cout<<"x_knts = "<<x_knts<<endl;
    cout<<"y_vals = "<<y_vals<<endl;
    pSLX = new class gsm::SelectivitySpline<dvar_vector,dvar_vector>(y_vals,x_knts);
    cout<<"z        = "<<x_knts<<endl;
    cout<<"sel      = "<<pSLX->Selectivity(x_knts)<<endl;
    cout<<"z        = "<<z<<endl;
    cout<<"sel      = "<<pSLX->Selectivity(z)<<endl;
    cout<<"logsel   = "<<pSLX->logSelectivity(z)<<endl;
    cout<<"logselM1 = "<<pSLX->logSelexMeanOne(z)<<endl;
    cout<<"--change knots and y_vals to check reallocation"<<endl;
    dvar_vector x_knts1(1,9);
    x_knts1[1]=z[1]; for (int i=1;i<=8;i++) x_knts1[i+1] = z[4*i];
    dvar_vector y_vals1 = 1.0/(1.0+exp(-(x_knts1-100.0)/30.0));
    ((gsm::SelectivitySpline<dvar_vector,dvar_vector>*)pSLX)->initSpline(y_vals1,x_knts1);
    cout<<"z        = "<<x_knts1<<endl;
    cout<<"sel      = "<<pSLX->Selectivity(x_knts1)<<endl;
    cout<<"z        = "<<z<<endl;
    cout<<"sel      = "<<pSLX->Selectivity(z)<<endl;
    cout<<"logsel   = "<<pSLX->logSelectivity(z)<<endl;
    cout<<"logselM1 = "<<pSLX->logSelexMeanOne(z)<<endl;
    exit(1);
    dvariable p1 = 30.0;
    dvariable p2 = 100.0;
    dvariable p3 = 50.0;
    cout<<"--DoubleNormal"<<endl;
    pSLX = new class gsm::DoubleNormal<dvar_vector,dvariable>(p1,p2,p3);
    cout<<z<<endl;
    cout<<pSLX->Selectivity(z)<<endl;
    cout<<pSLX->logSelectivity(z)<<endl;
    cout<<pSLX->logSelexMeanOne(z)<<endl;
    p1 = 30.0;
    p2 = 100.0;
    p3 = 50.0;
    dvariable p4 = 130.0;
    cout<<"--DoubleNormal4"<<endl;
    pSLX = new class gsm::DoubleNormal4<dvar_vector,dvariable>(p1,p2,p3,p4);
    cout<<z<<endl;
    cout<<pSLX->Selectivity(z)<<endl;
    cout<<pSLX->logSelectivity(z)<<endl;
    cout<<pSLX->logSelexMeanOne(z)<<endl;
    cout<<"--Uniform"<<endl;
    pSLX = new class gsm::UniformCurve<dvar_vector>();
    cout<<z<<endl;
    cout<<pSLX->Selectivity(z)<<endl;
    cout<<pSLX->logSelectivity(z)<<endl;
    cout<<pSLX->logSelexMeanOne(z)<<endl;
    cout<<"--Uniform0"<<endl;
    pSLX = new class gsm::Uniform0Curve<dvar_vector>();
    cout<<z<<endl;
    cout<<pSLX->Selectivity(z)<<endl;
    cout<<pSLX->logSelectivity(z)<<endl;
    cout<<pSLX->logSelexMeanOne(z)<<endl;
    exit(1);
  }
  theta.allocate(1,ntheta,theta_lb,theta_ub,theta_phz,"theta");
 ECHO(theta);
 cout<<"theta"<<theta<<endl;
  Grwth.allocate(1,nGrwth,Grwth_lb,Grwth_ub,Grwth_phz,"Grwth");
ECHO(Grwth);
  log_slx_pars.allocate(1,nslx_pars,slx_lb,slx_ub,slx_phzm,"log_slx_pars");
ECHO(log_slx_pars);
  Asymret.allocate(1,NumAsympRet,AsympSel_lb,AsympSel_ub,AsympSel_phz,"Asymret");
ECHO(Asymret);
  log_fbar.allocate(1,nfleet,fbar_lb,fbar_ub,f_phz,"log_fbar");
 ECHO(f_phz);
 ECHO(log_fbar);
  log_fdev.allocate(1,nfleet,1,nFparams,fdev_lb,fdev_ub,f_phz,"log_fdev");
 ECHO(nFparams);
 for (int I=1;I<=nfleet;I++) { ECHO(log_fdev(I)); }
  log_foff.allocate(1,nfleet,foff_lb,foff_ub,foff_phz,"log_foff");
 ECHO(log_foff);
 ECHO(foff_phz);
  log_fdov.allocate(1,nfleet,1,nYparams,-10,10,foff_phz,"log_fdov");
ECHO(nYparams);
 for (int I=1;I<=nfleet;I++) { ECHO(log_fdov(I)); }
  rec_ini.allocate(1,nclass,-14.0,14.0,rec_ini_phz,"rec_ini");
 ECHO(rec_ini);
  rec_dev_est.allocate(rdv_syr,rdv_eyr,-8.0,8.0,rdv_phz,"rec_dev_est");
 ECHO(rec_dev_est);
  rec_dev.allocate(syr,nyrRetro,"rec_dev");
  #ifndef NO_AD_INITIALIZE
    rec_dev.initialize();
  #endif
  logit_rec_prop_est.allocate(rdv_syr,rdv_eyr,-100,100,rec_prop_phz,"logit_rec_prop_est");
 ECHO(logit_rec_prop_est);
  logit_rec_prop.allocate(syr,nyrRetro,"logit_rec_prop");
  #ifndef NO_AD_INITIALIZE
    logit_rec_prop.initialize();
  #endif
  m_dev_est.allocate(1,nMdev,Mdev_lb,Mdev_ub,Mdev_phz,"m_dev_est");
 ECHO(nMdev);
  m_dev.allocate(1,nMdev,"m_dev");
  #ifndef NO_AD_INITIALIZE
    m_dev.initialize();
  #endif
 ECHO(nsex);
 ECHO(nMdev_par_cnt);
  m_dev_sex.allocate(1,nsex,1,nMdev_par_cnt,"m_dev_sex");
  #ifndef NO_AD_INITIALIZE
    m_dev_sex.initialize();
  #endif
 ECHO(m_dev_sex);
  Msize.allocate(1,nclass,"Msize");
  #ifndef NO_AD_INITIALIZE
    Msize.initialize();
  #endif
 ECHO(Msize);
  m_mat_mult.allocate(1,nsex,m_mat_lb,m_mat_ub,m_mat_phz,"m_mat_mult");
 ECHO(m_mat_mult);
  log_vn.allocate(1,nSizeComps,nvn_phz,"log_vn");
 ECHO(log_vn);
  survey_q.allocate(1,nSurveys,q_lb,q_ub,q_phz,"survey_q");
 ECHO(survey_q);
  log_add_cv.allocate(1,nSurveys,log_add_cv_lb,log_add_cv_ub,cv_phz,"log_add_cv");
 ECHO(log_add_cv);
  priorDensity.allocate(1,NVarPar,"priorDensity");
  #ifndef NO_AD_INITIALIZE
    priorDensity.initialize();
  #endif
  nloglike.allocate(1,nlikes,1,ilike_vector,"nloglike");
  #ifndef NO_AD_INITIALIZE
    nloglike.initialize();
  #endif
  nlogPenalty.allocate(1,9,"nlogPenalty");
  #ifndef NO_AD_INITIALIZE
    nlogPenalty.initialize();
  #endif
  sdnr_MAR_cpue.allocate(1,nSurveys,1,2,"sdnr_MAR_cpue");
  #ifndef NO_AD_INITIALIZE
    sdnr_MAR_cpue.initialize();
  #endif
  sdnr_MAR_lf.allocate(1,nSizeComps,1,2,"sdnr_MAR_lf");
  #ifndef NO_AD_INITIALIZE
    sdnr_MAR_lf.initialize();
  #endif
  Francis_weights.allocate(1,nSizeComps,"Francis_weights");
  #ifndef NO_AD_INITIALIZE
    Francis_weights.initialize();
  #endif
  objfun.allocate("objfun");
  prior_function_value.allocate("prior_function_value");
  likelihood_function_value.allocate("likelihood_function_value");
  M0.allocate(1,nsex,"M0");
  #ifndef NO_AD_INITIALIZE
    M0.initialize();
  #endif
  logR0.allocate("logR0");
  #ifndef NO_AD_INITIALIZE
  logR0.initialize();
  #endif
  logRbar.allocate("logRbar");
  #ifndef NO_AD_INITIALIZE
  logRbar.initialize();
  #endif
  logRini.allocate("logRini");
  #ifndef NO_AD_INITIALIZE
  logRini.initialize();
  #endif
  ra.allocate(1,nsex,"ra");
  #ifndef NO_AD_INITIALIZE
    ra.initialize();
  #endif
  rbeta.allocate(1,nsex,"rbeta");
  #ifndef NO_AD_INITIALIZE
    rbeta.initialize();
  #endif
  logSigmaR.allocate("logSigmaR");
  #ifndef NO_AD_INITIALIZE
  logSigmaR.initialize();
  #endif
  steepness.allocate("steepness");
  #ifndef NO_AD_INITIALIZE
  steepness.initialize();
  #endif
  rho.allocate("rho");
  #ifndef NO_AD_INITIALIZE
  rho.initialize();
  #endif
  logN0.allocate(1,n_grp,1,nclass,"logN0");
  #ifndef NO_AD_INITIALIZE
    logN0.initialize();
  #endif
  alpha.allocate(1,nsex,"alpha");
  #ifndef NO_AD_INITIALIZE
    alpha.initialize();
  #endif
  beta.allocate(1,nsex,"beta");
  #ifndef NO_AD_INITIALIZE
    beta.initialize();
  #endif
  rec_sdd.allocate(1,nsex,1,nclass,"rec_sdd");
  #ifndef NO_AD_INITIALIZE
    rec_sdd.initialize();
  #endif
  gscale.allocate(1,nsex,1,maxSizeIncVaries,"gscale");
  #ifndef NO_AD_INITIALIZE
    gscale.initialize();
  #endif
  molt_mu.allocate(1,nsex,1,nMoltVaries,"molt_mu");
  #ifndef NO_AD_INITIALIZE
    molt_mu.initialize();
  #endif
  molt_cv.allocate(1,nsex,1,nMoltVaries,"molt_cv");
  #ifndef NO_AD_INITIALIZE
    molt_cv.initialize();
  #endif
  Linf.allocate(1,nsex,1,maxSizeIncVaries,"Linf");
  #ifndef NO_AD_INITIALIZE
    Linf.initialize();
  #endif
  Kappa.allocate(1,nsex,1,maxSizeIncVaries,"Kappa");
  #ifndef NO_AD_INITIALIZE
    Kappa.initialize();
  #endif
  SigmaKappa.allocate(1,nsex,1,maxSizeIncVaries,"SigmaKappa");
  #ifndef NO_AD_INITIALIZE
    SigmaKappa.initialize();
  #endif
  SigmaLinf.allocate(1,nsex,1,maxSizeIncVaries,"SigmaLinf");
  #ifndef NO_AD_INITIALIZE
    SigmaLinf.initialize();
  #endif
  recruits.allocate(1,nsex,syr,nyrRetro,"recruits");
  #ifndef NO_AD_INITIALIZE
    recruits.initialize();
  #endif
  res_recruit.allocate(syr,nyrRetro,"res_recruit");
  #ifndef NO_AD_INITIALIZE
    res_recruit.initialize();
  #endif
  xi.allocate(syr,nyrRetro,"xi");
  #ifndef NO_AD_INITIALIZE
    xi.initialize();
  #endif
  pre_catch.allocate(1,nCatchDF,1,nCatchRows,"pre_catch");
  #ifndef NO_AD_INITIALIZE
    pre_catch.initialize();
  #endif
  res_catch.allocate(1,nCatchDF,1,nCatchRows,"res_catch");
  #ifndef NO_AD_INITIALIZE
    res_catch.initialize();
  #endif
  obs_catch_effort.allocate(1,nCatchDF,1,nCatchRows,"obs_catch_effort");
  #ifndef NO_AD_INITIALIZE
    obs_catch_effort.initialize();
  #endif
  pre_catch_out.allocate(1,nCatchDF,syr,nyrRetro,"pre_catch_out");
  #ifndef NO_AD_INITIALIZE
    pre_catch_out.initialize();
  #endif
  res_catch_out.allocate(1,nCatchDF,syr,nyrRetro,"res_catch_out");
  #ifndef NO_AD_INITIALIZE
    res_catch_out.initialize();
  #endif
  log_q_catch.allocate(1,nCatchDF,"log_q_catch");
  #ifndef NO_AD_INITIALIZE
    log_q_catch.initialize();
  #endif
  molt_increment.allocate(1,nsex,1,maxSizeIncVaries,1,nclass,"molt_increment");
  #ifndef NO_AD_INITIALIZE
    molt_increment.initialize();
  #endif
  molt_probability.allocate(1,nsex,syr,nyr,1,nclass,"molt_probability");
  #ifndef NO_AD_INITIALIZE
    molt_probability.initialize();
  #endif
  molt_probability_in.allocate(1,nsex,1,maxSizeIncVaries,1,nclass,"molt_probability_in");
  #ifndef NO_AD_INITIALIZE
    molt_probability_in.initialize();
  #endif
  ProbMolt.allocate(1,nsex,1,nclass,1,nclass,"ProbMolt");
  #ifndef NO_AD_INITIALIZE
    ProbMolt.initialize();
  #endif
  growth_transition.allocate(1,nsex,1,maxSizeIncVaries,1,nclass,1,nclass,"growth_transition");
  #ifndef NO_AD_INITIALIZE
    growth_transition.initialize();
  #endif
  log_slx_capture.allocate(1,nfleet,1,nsex,syr,nyrRetro+1,1,nclass,"log_slx_capture");
  #ifndef NO_AD_INITIALIZE
    log_slx_capture.initialize();
  #endif
  log_slx_retaind.allocate(1,nfleet,1,nsex,syr,nyrRetro+1,1,nclass,"log_slx_retaind");
  #ifndef NO_AD_INITIALIZE
    log_slx_retaind.initialize();
  #endif
  log_slx_discard.allocate(1,nfleet,1,nsex,syr,nyrRetro+1,1,nclass,"log_slx_discard");
  #ifndef NO_AD_INITIALIZE
    log_slx_discard.initialize();
  #endif
  log_high_grade.allocate(1,nfleet,1,nsex,syr,nyrRetro+1,"log_high_grade");
  #ifndef NO_AD_INITIALIZE
    log_high_grade.initialize();
  #endif
  M.allocate(1,nsex,1,nmature,syr,nyrRetro,1,nclass,"M");
  #ifndef NO_AD_INITIALIZE
    M.initialize();
  #endif
  Mmult.allocate(1,nclass,"Mmult");
  #ifndef NO_AD_INITIALIZE
    Mmult.initialize();
  #endif
  fout.allocate(1,nfleet,syr,nyrRetro,"fout");
  #ifndef NO_AD_INITIALIZE
    fout.initialize();
  #endif
  finit.allocate(1,nfleet,"finit");
  #ifndef NO_AD_INITIALIZE
    finit.initialize();
  #endif
  ft.allocate(1,nfleet,1,nsex,syr,nyrRetro,1,nseason,"ft");
  #ifndef NO_AD_INITIALIZE
    ft.initialize();
  #endif
  F.allocate(1,nsex,syr,nyrRetro,1,nseason,1,nclass,"F");
  #ifndef NO_AD_INITIALIZE
    F.initialize();
  #endif
  F2.allocate(1,nsex,syr,nyrRetro,1,nseason,1,nclass,"F2");
  #ifndef NO_AD_INITIALIZE
    F2.initialize();
  #endif
  Z.allocate(1,nsex,1,nmature,syr,nyrRetro,1,nseason,1,nclass,"Z");
  #ifndef NO_AD_INITIALIZE
    Z.initialize();
  #endif
  Z2.allocate(1,nsex,1,nmature,syr,nyrRetro,1,nseason,1,nclass,"Z2");
  #ifndef NO_AD_INITIALIZE
    Z2.initialize();
  #endif
  S.allocate(1,nsex,1,nmature,syr,nyrRetro,1,nseason,1,nclass,1,nclass,"S");
  #ifndef NO_AD_INITIALIZE
    S.initialize();
  #endif
  d4_N.allocate(1,n_grp,syr,nyrRetro+1,1,nseason,1,nclass,"d4_N");
  #ifndef NO_AD_INITIALIZE
    d4_N.initialize();
  #endif
  d3_newShell.allocate(1,nsex,syr,nyrRetro+1,1,nclass,"d3_newShell");
  #ifndef NO_AD_INITIALIZE
    d3_newShell.initialize();
  #endif
  d3_oldShell.allocate(1,nsex,syr,nyrRetro+1,1,nclass,"d3_oldShell");
  #ifndef NO_AD_INITIALIZE
    d3_oldShell.initialize();
  #endif
  TempSS.allocate("TempSS");
  #ifndef NO_AD_INITIALIZE
  TempSS.initialize();
  #endif
  pre_cpue.allocate(1,nSurveyRows,"pre_cpue");
  #ifndef NO_AD_INITIALIZE
    pre_cpue.initialize();
  #endif
  res_cpue.allocate(1,nSurveyRows,"res_cpue");
  #ifndef NO_AD_INITIALIZE
    res_cpue.initialize();
  #endif
  d3_pre_size_comps_in.allocate(1,nSizeComps_in,1,nSizeCompRows_in,1,nSizeCompCols_in,"d3_pre_size_comps_in");
  #ifndef NO_AD_INITIALIZE
    d3_pre_size_comps_in.initialize();
  #endif
  d3_res_size_comps_in.allocate(1,nSizeComps_in,1,nSizeCompRows_in,1,nSizeCompCols_in,"d3_res_size_comps_in");
  #ifndef NO_AD_INITIALIZE
    d3_res_size_comps_in.initialize();
  #endif
  d3_obs_size_comps_out.allocate(1,nSizeComps_in,1,nSizeCompRows_in,1,nSizeCompCols_in,"d3_obs_size_comps_out");
  #ifndef NO_AD_INITIALIZE
    d3_obs_size_comps_out.initialize();
  #endif
  d3_pre_size_comps_out.allocate(1,nSizeComps_in,1,nSizeCompRows_in,1,nSizeCompCols_in,"d3_pre_size_comps_out");
  #ifndef NO_AD_INITIALIZE
    d3_pre_size_comps_out.initialize();
  #endif
  d3_res_size_comps_out.allocate(1,nSizeComps_in,1,nSizeCompRows_in,1,nSizeCompCols_in,"d3_res_size_comps_out");
  #ifndef NO_AD_INITIALIZE
    d3_res_size_comps_out.initialize();
  #endif
  d3_pre_size_comps.allocate(1,nSizeComps,1,nSizeCompRows,1,nSizeCompCols,"d3_pre_size_comps");
  #ifndef NO_AD_INITIALIZE
    d3_pre_size_comps.initialize();
  #endif
  d3_res_size_comps.allocate(1,nSizeComps,1,nSizeCompRows,1,nSizeCompCols,"d3_res_size_comps");
  #ifndef NO_AD_INITIALIZE
    d3_res_size_comps.initialize();
  #endif
  FullY.allocate(1,nsex,1,maxSizeIncVaries,1,MaxGrowTimeLib,1,nclass,1,nclass,"FullY");
  #ifndef NO_AD_INITIALIZE
    FullY.initialize();
  #endif
  ssb_pass.allocate("ssb_pass");
  #ifndef NO_AD_INITIALIZE
  ssb_pass.initialize();
  #endif
  ofltot_pass.allocate("ofltot_pass");
  #ifndef NO_AD_INITIALIZE
  ofltot_pass.initialize();
  #endif
  oflret_pass.allocate("oflret_pass");
  #ifndef NO_AD_INITIALIZE
  oflret_pass.initialize();
  #endif
  log_fimpbar.allocate(1,nfleet,"log_fimpbar");
  #ifndef NO_AD_INITIALIZE
    log_fimpbar.initialize();
  #endif
  log_fimpbarOFL.allocate(1,nfleet,"log_fimpbarOFL");
  #ifndef NO_AD_INITIALIZE
    log_fimpbarOFL.initialize();
  #endif
  log_fimpbarPass.allocate(1,nfleet,"log_fimpbarPass");
  #ifndef NO_AD_INITIALIZE
    log_fimpbarPass.initialize();
  #endif
  catch_pass.allocate(1,2+nfleet,"catch_pass");
  #ifndef NO_AD_INITIALIZE
    catch_pass.initialize();
  #endif
  dvar_mid_points.allocate(1,nclass,"dvar_mid_points");
  #ifndef NO_AD_INITIALIZE
    dvar_mid_points.initialize();
  #endif
dvar_mid_points = mid_points;
  spr_rbar.allocate("spr_rbar");
  #ifndef NO_AD_INITIALIZE
  spr_rbar.initialize();
  #endif
  spr_sexr.allocate("spr_sexr");
  #ifndef NO_AD_INITIALIZE
  spr_sexr.initialize();
  #endif
  ssbF0.allocate("ssbF0");
  #ifndef NO_AD_INITIALIZE
  ssbF0.initialize();
  #endif
  spr_bmsy.allocate("spr_bmsy");
  #ifndef NO_AD_INITIALIZE
  spr_bmsy.initialize();
  #endif
  spr_depl.allocate("spr_depl");
  #ifndef NO_AD_INITIALIZE
  spr_depl.initialize();
  #endif
  spr_cofl.allocate("spr_cofl");
  #ifndef NO_AD_INITIALIZE
  spr_cofl.initialize();
  #endif
  spr_fofl.allocate("spr_fofl");
  #ifndef NO_AD_INITIALIZE
  spr_fofl.initialize();
  #endif
  Bmsy.allocate("Bmsy");
  #ifndef NO_AD_INITIALIZE
  Bmsy.initialize();
  #endif
  SR_alpha_prj.allocate("SR_alpha_prj");
  #ifndef NO_AD_INITIALIZE
  SR_alpha_prj.initialize();
  #endif
  SR_beta_prj.allocate("SR_beta_prj");
  #ifndef NO_AD_INITIALIZE
  SR_beta_prj.initialize();
  #endif
  Steepness.allocate("Steepness");
  #ifndef NO_AD_INITIALIZE
  Steepness.initialize();
  #endif
  spr_yield.allocate(0,100,1,4,"spr_yield");
  #ifndef NO_AD_INITIALIZE
    spr_yield.initialize();
  #endif
  fut_recruits.allocate(1,nsex,1,nproj,"fut_recruits");
  #ifndef NO_AD_INITIALIZE
    fut_recruits.initialize();
  #endif
  sd_fbar.allocate(syr,nyr-1,"sd_fbar");
  #ifndef NO_AD_INITIALIZE
    sd_fbar.initialize();
  #endif
  sd_log_dyn_Bzero.allocate(syr+1,nyr,"sd_log_dyn_Bzero");
  #ifndef NO_AD_INITIALIZE
    sd_log_dyn_Bzero.initialize();
  #endif
  sd_rbar.allocate("sd_rbar");
  sd_ssbF0.allocate("sd_ssbF0");
  sd_Bmsy.allocate("sd_Bmsy");
  sd_depl.allocate("sd_depl");
  sd_fmsy.allocate(1,nfleet,"sd_fmsy");
  sd_fofl.allocate(1,nfleet,"sd_fofl");
  sd_ofl.allocate("sd_ofl");
  sd_log_recruits.allocate(1,nsex,syr,nyr,"sd_log_recruits");
  sd_log_ssb.allocate(syr,nyr,"sd_log_ssb");
  sd_last_ssb.allocate("sd_last_ssb");
  ParsOut.allocate(1,NVarPar,"ParsOut");
}

void model_parameters::preliminary_calculations(void)
{

#if defined(USE_ADPVM)

  admaster_slave_variable_interface(*this);

#endif
  dvector rands(1,1000);
  dvector randu(1,1000);
  cout << "+----------------------+" << endl;
  cout << "| Preliminary section  |" << endl;
  cout << "+----------------------+" << endl;
  // 32 Gaussian evaluation points
  xg( 1)=-0.99726; xg( 2)=-0.98561; xg( 3)=-0.96476; xg( 4)=-0.93490; xg( 5)=-0.89632; xg( 6)=-0.84936; xg( 7)=-0.79448; xg( 8)=-0.73218;
  xg( 9)=-0.66304; xg(10)=-0.58771; xg(11)=-0.50689; xg(12)=-0.42135; xg(13)=-0.33186; xg(14)=-0.23928; xg(15)=-0.14447; xg(16)= -0.0483;
  xg(17)= 0.04830; xg(18)= 0.14447; xg(19)= 0.23928; xg(20)= 0.33186; xg(21)= 0.42135 ;xg(22)= 0.50689; xg(23)= 0.58771; xg(24)= 0.66304;
  xg(25)= 0.73218; xg(26)= 0.79448; xg(27)= 0.84936; xg(28)= 0.89632; xg(29)= 0.93490; xg(30)= 0.96476; xg(31)= 0.98561; xg(32)= 0.99726;
  // 32 Gaussian weights
  wg( 1)=0.00701; wg( 2)=0.01627; wg( 3)=0.02539; wg( 4)=0.03427; wg( 5)=0.04283; wg( 6)=0.05099; wg( 7)=0.05868; wg( 8)=0.06582;
  wg( 9)=0.07234; wg(10)=0.07819; wg(11)=0.08331; wg(12)=0.08765; wg(13)=0.09117; wg(14)=0.09384; wg(15)=0.09563; wg(16)=0.09654;
  wg(17)=0.09654; wg(18)=0.09563; wg(19)=0.09384; wg(20)=0.09117; wg(21)=0.08765; wg(22)=0.08331; wg(23)=0.07819; wg(24)=0.07234;
  wg(25)=0.06582; wg(26)=0.05868; wg(27)=0.05099; wg(28)=0.04283; wg(29)=0.03427; wg(30)=0.02539; wg(31)=0.01627; wg(32)=0.00701;
  // evaluation points for l1 based on initial size class
  for (int h=1;h<=nsex;h++)
   for(int i=1; i<=32; i++)
    for(int j=1; j<=nclass; j++)
     l1_vec(h,j,i) = ((xg(i) + 1)/2)*(size_breaks(j+1)-size_breaks(j)) + size_breaks(j);
  if ( simflag )
   {
    if ( !global_parfile )
     {
      cerr << "Must have a gmacs.pin file to use the -sim command line option" << endl;
      ad_exit(1);
     }
    cout << "|-------------------------------------------|" << endl;
    cout << "|*** RUNNING SIMULATION WITH RSEED = " << rseed << " ***|" << endl;
    cout << "|-------------------------------------------|" << endl;
    simulation_model();
    //exit(1);
   }
  random_number_generator rng2( start ) ;
  if (IsJittered!=0)
   {
    cout << "+------------------------------+" << endl;
    cout << "| Jittering                    |" << endl;
    cout << "+------------------------------+" << endl;
    for (int ipar=1;ipar<=ntheta;ipar++)  
     {
      rands.fill_randn(rng2);
      randu.fill_randn(rng2);
      theta(ipar) = GenJitter(IsJittered,theta_ival(ipar),theta_lb(ipar),theta_ub(ipar),theta_phz(ipar),sdJitter,rands,randu);
     } 
    for (int ipar=1;ipar<=nGrwth;ipar++)  
     {
      rands.fill_randn(rng2);
      randu.fill_randn(rng2);
      Grwth(ipar) = GenJitter(IsJittered,Grwth_ival(ipar),Grwth_lb(ipar),Grwth_ub(ipar),Grwth_phz(ipar),sdJitter,rands,randu);
     } 
    for (int ipar=1;ipar<=nslx_pars;ipar++)  
     {
      rands.fill_randn(rng2);
      randu.fill_randn(rng2);
      log_slx_pars(ipar) = GenJitter(IsJittered,log_slx_pars_init(ipar),slx_lb(ipar),slx_ub(ipar),slx_phzm(ipar),sdJitter,rands,randu);
     } 
    for (int ipar=1;ipar<=NumAsympRet;ipar++)  
     {
      rands.fill_randn(rng2);
      randu.fill_randn(rng2);
      Asymret(ipar) = GenJitter(IsJittered,AsympSel_ival(ipar),AsympSel_lb(ipar),AsympSel_ub(ipar),AsympSel_phz(ipar),sdJitter,rands,randu);
     } 
    for (int ipar=1;ipar<=nfleet;ipar++)  
     {
      rands.fill_randn(rng2);
      randu.fill_randn(rng2);
      log_fbar(ipar) = GenJitter(IsJittered,log_pen_fbar(ipar),fbar_lb(ipar),fbar_ub(ipar),f_phz(ipar),sdJitter,rands,randu);
     } 
    for (int ipar=1;ipar<=nfleet;ipar++)  
     for (int jpar=1;jpar<=nFparams(ipar); jpar++)
      {
       rands.fill_randn(rng2);
       randu.fill_randn(rng2);
       log_fdev(ipar,jpar) = GenJitter(IsJittered,(fdev_ub(ipar)+fdev_lb(ipar))/2.0,fdev_lb(ipar),fdev_ub(ipar),f_phz(ipar),sdJitter,rands,randu);
      } 
    for (int ipar=1;ipar<=nfleet;ipar++)  
     {
      rands.fill_randn(rng2);
      randu.fill_randn(rng2);
      log_foff(ipar) = GenJitter(IsJittered,(foff_ub(ipar)+foff_lb(ipar))/2.0,foff_lb(ipar),foff_ub(ipar),foff_phz(ipar),sdJitter,rands,randu);
     } 
    for (int ipar=1;ipar<=nfleet;ipar++)  
     for (int jpar=1;jpar<=nYparams(ipar); jpar++)
      {
       rands.fill_randn(rng2);
       randu.fill_randn(rng2);
       log_fdov(ipar,jpar) = GenJitter(IsJittered,0.0,-10.0,10.0,foff_phz(ipar),sdJitter,rands,randu);
      } 
    for (int ipar=1;ipar<=nclass;ipar++)  
     {
      rands.fill_randn(rng2);
      randu.fill_randn(rng2);
      rec_ini(ipar) = GenJitter(IsJittered,0.0,-14.0,14.0,rec_ini_phz,sdJitter,rands,randu);
     } 
    for (int ipar=rdv_syr;ipar<=rdv_eyr;ipar++)  
     {
      rands.fill_randn(rng2);
      randu.fill_randn(rng2);
      rec_dev_est(ipar) = GenJitter(IsJittered,0.0,-8.0,8.0,rdv_phz,sdJitter,rands,randu);
     } 
    for (int ipar=rdv_syr;ipar<=rdv_eyr;ipar++)  
     {
      rands.fill_randn(rng2);
      randu.fill_randn(rng2);
      logit_rec_prop_est(ipar) = GenJitter(IsJittered,init_sex_ratio,-100.0,100.0,rec_prop_phz,sdJitter,rands,randu);
     } 
    for (int ipar=1;ipar<=nMdev;ipar++)  
     {
      rands.fill_randn(rng2);
      randu.fill_randn(rng2);
      m_dev_est(ipar) = GenJitter(IsJittered,Mdev_ival(ipar),Mdev_lb(ipar),Mdev_ub(ipar),Mdev_phz(ipar),sdJitter,rands,randu);
     } 
    for (int ipar=1;ipar<=nSizeComps;ipar++)  
     {
      rands.fill_randn(rng2);
      randu.fill_randn(rng2);
      log_vn(ipar) = GenJitter(IsJittered,log_nvn_ival(ipar),-10.0,10.0,nvn_phz(ipar),sdJitter,rands,randu);
     } 
    for (int ipar=1;ipar<=nSurveys;ipar++)  
     {
      rands.fill_randn(rng2);
      randu.fill_randn(rng2);
      survey_q(ipar) = GenJitter(IsJittered,q_ival(ipar),q_lb(ipar),q_ub(ipar),q_phz(ipar),sdJitter,rands,randu);
     } 
    for (int ipar=1;ipar<=nSurveys;ipar++)  
     {
      rands.fill_randn(rng2);
      randu.fill_randn(rng2);
      log_add_cv(ipar) = GenJitter(IsJittered,log_add_cv_ival(ipar),log_add_cv_lb(ipar),log_add_cv_ub(ipar),cv_phz(ipar),sdJitter,rands,randu);
     } 
   }   
  cout << "+------------------------------+" << endl;
  cout << "| Initial Procedure Section    |" << endl;
  cout << "+------------------------------+" << endl;
  initialize_model_parameters();            if ( verbose >= 3 ) cout << "Ok after initialize_model_parameters in Prelim ..." << endl;
  calc_growth_increments();                 if ( verbose >= 3 ) cout << "Ok after calc_growth_increments in Prelim ..." << endl;
  calc_molting_probability();               if ( verbose >= 3 ) cout << "Ok after calc_molting_probability in Prelim ..." << endl;
  for ( int h = 1; h <= nsex; h++ )
   for ( int l = 1; l <= nclass; l++ )
    if (molt_increment(h,1,l) < 0)
     {
       cout << "Error: Initial value of the growth increment for sex " << h << " and size-class " << l << " is negative: " << molt_increment(h,1,l) << "; STOPPING" << endl; 
       exit(1); 
     }
  calc_growth_transition();                 if ( verbose >= 3 ) cout << "Ok after calc_growth_transition in Prelim ..." << endl;
  init_selectivities();                     if ( verbose >= 3 ) cout << "Ok after init_selectivities in Prelim ..." << endl;
  calc_selectivities();                     if ( verbose >= 3 ) cout << "Ok after calc_selectivities in Prelim ..." << endl;
}

void model_parameters::between_phases_calculations(void)
{
    cout<<endl;
    cout<<"#--BETWEEN_PHASES_SECTION---------------------"<<endl;
    adstring msg = "#----Starting phase "+str(current_phase())+" of "+str(initial_params::max_number_phases);
    cout<<msg<<endl;
    cout<<"----------------------------------------------"<<endl;
}

void model_parameters::userfunction(void)
{
  objfun =0.0;
  int Ipnt,ii,jj;
  //cout << theta << endl;
  //cout << Grwth << endl;
  //cout << log_slx_pars << endl;
  //exit(1);
  if ( verbose >= 3 ) cout << "Ok after start of function ..." << endl;
  // Update function calls
  NfunCall += 1;
  // Initialize model parameters
  initialize_model_parameters();                           if ( verbose >= 3 ) cout << "Ok after initialize_model_parameters ..." << endl;
  // Fishing fleet dynamics ...
  if (current_phase() >= PhaseSelexPar)
   calc_selectivities();                                   if ( verbose >= 3 ) cout << "Ok after calc_selectivities ..." << endl;
  else
   if ( verbose >= 3 ) cout << "Ok after ignoring selex calculation..." << endl;
  calc_fishing_mortality();                                if ( verbose >= 3 ) cout << "Ok after calc_fishing_mortality ..." << endl;
  calc_natural_mortality();                                if ( verbose >= 3 ) cout << "Ok after calc_natural_mortality ..." << endl;
  calc_total_mortality();                                  if ( verbose >= 3 ) cout << "Ok after calc_total_mortality ..." << endl;
  // growth ...
  if (current_phase() >= PhaseGrowthPar)
   {
    calc_growth_increments();                              if ( verbose >= 3 ) cout << "Ok after calc_growth_increments ..." << endl;
    calc_molting_probability();                            if ( verbose >= 3 ) cout << "Ok after calc_molting_probability ..." << endl;
    calc_growth_transition();                              if ( verbose >= 3 ) cout << "Ok after calc_growth_transition ..." << endl;
   }
  else
   if ( verbose >= 3 ) cout << "Ok after ignoring growth calculation..." << endl;
  calc_recruitment_size_distribution();                    if ( verbose >= 3 ) cout << "Ok after calc_recruitment_size_distribution ..." << endl;
  calc_initial_numbers_at_length();                        if ( verbose >= 3 ) cout << "Ok after calc_initial_numbers_at_length ..." << endl;
  update_population_numbers_at_length();                   if ( verbose >= 3 ) cout << "Ok after update_population_numbers_at_length ..." << endl;
  //calc_stock_recruitment_relationship();                   if ( verbose >= 3 ) cout << "Ok after calc_stock_recruitment_relationship ..." << endl;
  // observation models ...
  calc_predicted_catch();                                  if ( verbose >= 3 ) cout << "Ok after calc_predicted_catch ..." << endl;
  calc_relative_abundance();                               if ( verbose >= 3 ) cout << "Ok after calc_relative_abundance ..." << endl;
  calc_predicted_composition();                            if ( verbose >= 3 ) cout << "Ok after calc_predicted_composition ..." << endl;
  if ( verbose >= 3 ) cout << "Ok after observation models ..." << endl;
  // objective function ...
  calc_prior_densities();                                  if ( verbose >= 3 ) cout << "Ok after calc_prior_densities ..." << endl;
  calc_objective_function();                               if ( verbose >= 3 ) cout << "Ok after calc_objective_function ..." << endl;
  // sd_report variables
  if ( sd_phase() )
   {
      if ( verbose >= 3 ) cout<<"Starting sd_phase"<<endl;
  // Save the estimates parameters to ParsOut (used for variance estimation)        
  Ipnt = 0;
  for (ii=1;ii<=ntheta;ii++) if (theta_phz(ii) > 0) {Ipnt +=1; ParsOut(Ipnt) = theta(ii); }
  for (ii=1;ii<=nGrwth; ii++) if (Grwth_phz(ii) > 0) {Ipnt +=1; ParsOut(Ipnt) = Grwth(ii); }
  for (ii=1;ii<=nslx_pars; ii++) if (slx_phzm(ii) > 0) {Ipnt +=1; ParsOut(Ipnt) = log_slx_pars(ii); }
  for (ii=1;ii<=NumAsympRet; ii++) if (AsympSel_phz(ii) > 0) {Ipnt +=1; ParsOut(Ipnt) = Asymret(ii); }
  for (ii=1;ii<=nfleet; ii++) if (f_phz(ii) > 0) {Ipnt +=1; ParsOut(Ipnt) = log_fbar(ii); }
  for (ii=1;ii<=nfleet; ii++)
   for (jj=1;jj<=nFparams(ii);jj++) if (f_phz(ii) > 0) {Ipnt +=1; ParsOut(Ipnt) = log_fdev(ii,jj); }
  for (ii=1;ii<=nfleet; ii++) if (foff_phz(ii) > 0) {Ipnt +=1; ParsOut(Ipnt) = log_foff(ii); }
  for (ii=1;ii<=nfleet; ii++)
  if (nYparams(ii) > 0 & foff_phz(ii) > 0)
   {
    for (jj=1;jj<=nYparams(ii);jj++) {Ipnt +=1; ParsOut(Ipnt) = log_fdov(ii,jj); }
   }
  for (ii=1;ii<=nclass; ii++) if (rec_ini_phz > 0) {Ipnt +=1; ParsOut(Ipnt) = rec_ini(ii); }
  for (ii=rdv_syr;ii<=rdv_eyr; ii++) if (rdv_phz > 0) {Ipnt +=1; ParsOut(Ipnt) = rec_dev_est(ii); }
  for (ii=rdv_syr;ii<=rdv_eyr; ii++) if (rec_prop_phz > 0) {Ipnt +=1; ParsOut(Ipnt) = logit_rec_prop_est(ii); }
  for (ii=1;ii<=nMdev; ii++) if (Mdev_phz(ii) > 0) {Ipnt +=1; ParsOut(Ipnt) = m_dev_est(ii); }
  for (ii=1;ii<=nsex; ii++) if (m_mat_phz(ii) > 0) {Ipnt +=1; ParsOut(Ipnt) = m_mat_mult(ii); }
  for (ii=1;ii<=nSizeComps; ii++) if (nvn_phz(ii) > 0) {Ipnt +=1; ParsOut(Ipnt) = log_vn(ii); }
  for (ii=1;ii<=nSurveys; ii++) if (q_phz(ii) > 0) {Ipnt +=1; ParsOut(Ipnt) = survey_q(ii); }
  for (ii=1;ii<=nSurveys; ii++) if (cv_phz(ii) > 0) {Ipnt +=1; ParsOut(Ipnt) = log_add_cv(ii); }
    calc_spr_reference_points2(0);
    if ( verbose >= 3 ) cout << "Ok after calc_spr_reference_points ..." << endl;
    calc_sdreport();
    if ( verbose >= 3 ) cout << "Ok after calc_sdreport ..." << endl;
   }
  // General outputs
  if ( mceval_phase() ) write_eval();
  if ( NfunCall == StopAfterFnCall ) {
      CreateOutput();         
      cout<<"--------------------------------------"<<endl;        
      cout<<"Stopping after "<<StopAfterFnCall<<" function calls"<<endl;        
      cout<<"--------------------------------------"<<endl;        
      exit(1);         
  }        
  /**
   * @brief Initialize model parameters
   * @details Set global variable equal to the estimated parameter vectors.
   *
  **/
}

void model_parameters::initialize_model_parameters(void)
{
  int Ipnt, Jpnt, Ihmo;
  // Get parameters from theta control matrix:
  M0(1)      = theta(1);
  Jpnt = 2;
  if (nsex>1)
   {
    if (MrelFem==YES) M0(2) = M0(1)*exp(theta(2));
    if (MrelFem==NO) M0(2) = theta(2);
    Jpnt = 3;
   }
  logR0     = theta(Jpnt);
  logRini   = theta(Jpnt+1);
  logRbar   = theta(Jpnt+2);
  ra(1)     = theta(Jpnt+3);
  rbeta(1)  = theta(Jpnt+4);
  Jpnt = Jpnt + 5;
  if (nsex>1)
   {
    ra(2)     = ra(1)*exp(theta(Jpnt));
    rbeta(2)  = rbeta(1)*exp(theta(Jpnt+1));
    Jpnt += 2;
   }
  logSigmaR = theta(Jpnt);
  steepness = theta(Jpnt+1);
  rho       = theta(Jpnt+2);
  Jpnt = Jpnt + 2;
  // Set rec_deviations
  rec_dev.initialize();
  logit_rec_prop.initialize();
  for ( int i = rdv_syr; i <= rdv_eyr; i++)
   {
    rec_dev(i) = rec_dev_est(i);
    logit_rec_prop(i) = logit_rec_prop_est(i);
   }
  // Estimate initial numbers as absolute
  if ( bInitializeUnfished == FREEPARS )
   {
    Ipnt = 0;
    for ( int h = 1; h <= nsex; h++ )
     for ( int m = 1; m <= nmature; m++ )
      for ( int o = 1; o <= nshell; o++ )
       {
        Ihmo = pntr_hmo(h,m,o);
        for ( int l = 1; l <= nclass; l++ )
         {
          Ipnt += 1;
          logN0(Ihmo,l) = theta(Jpnt+Ipnt);
         }
       }
    }
  // Estimate initial numbers as logistic offsest
  TempSS = 0;
  if ( bInitializeUnfished == FREEPARSSCALED )
   {
    Ipnt = 0;
    for ( int h = 1; h <= nsex; h++ )
     for ( int m = 1; m <= nmature; m++ )
      for ( int o = 1; o <= nshell; o++ )
       {
        Ihmo = pntr_hmo(h,m,o);
        for ( int l = 1; l <= nclass; l++ )
         {
          if (Ipnt==0)
           logN0(Ihmo,1) = 0;
          else
            { logN0(Ihmo,l) = theta(Jpnt+Ipnt);
              if (active(theta(Jpnt+Ipnt)))
               TempSS += theta(Jpnt+Ipnt)*theta(Jpnt+Ipnt); }
          Ipnt += 1;
         }
       }
   }
  // Get Growth & Molting parameters
  int icnt = 1;
  for ( int h = 1; h <= nsex; h++ )
   for ( int igrow = 1; igrow<=nSizeIncVaries(h); igrow++)
    {
     if (bUseGrowthIncrementModel==LINEAR_GROWTHMODEL)
      {
       alpha(h)   = Grwth(icnt);
       beta(h)    = Grwth(icnt+1);
       gscale(h,igrow)  = Grwth(icnt+2);
       icnt += 3;
      }
     if (bUseGrowthIncrementModel==INDIVIDUAL_GROWTHMODEL1 | bUseGrowthIncrementModel==INDIVIDUAL_GROWTHMODEL2)
      {
       for (int l=1; l<=nclass;l++) molt_increment(h,igrow,l) = Grwth(icnt+l-1);
       if (BetaParRelative==NO || igrow==1)
        gscale(h,igrow)  = Grwth(icnt+nclass);
       else
        if (BetaParRelative==YES) gscale(h,igrow)  = exp(Grwth(icnt+nclass))*gscale(h,1);
       icnt += (nclass+1);
      }
     // Kappa varies
     if (bUseGrowthIncrementModel==GROWTH_VARYK)
      {
       Linf(h,igrow)       = Grwth(icnt);
       Kappa(h,igrow)      = Grwth(icnt+1);
       SigmaKappa(h,igrow) = Grwth(icnt+2);
       icnt += 3;
      }
     // Linf varies
     if (bUseGrowthIncrementModel==GROWTH_VARYLINF)
      {
       Linf(h,igrow)       = Grwth(icnt);
       Kappa(h,igrow)      = Grwth(icnt+1);
       SigmaLinf(h,igrow)  = Grwth(icnt+2);
       icnt += 3;
      }
     // Linf and Kappa varies
     if (bUseGrowthIncrementModel==GROWTH_VARYKLINF)
      {
       Linf(h,igrow)       = Grwth(icnt);
       Kappa(h,igrow)      = Grwth(icnt+1);
       SigmaLinf(h,igrow)  = Grwth(icnt+2);
       SigmaKappa(h,igrow) = Grwth(icnt+3);
       icnt += 4;
      }
    }
   for ( int h = 1; h <= nsex; h++ )
    for (int igrow=1;igrow<=nMoltVaries(h);igrow++)
	{
     if (bUseCustomMoltProbility == LOGISTIC_PROB_MOLT)
      {
       molt_mu(h,igrow) = Grwth(icnt);
       molt_cv(h,igrow) = Grwth(icnt+1);
       icnt = icnt + 2;
      }
	 if (bUseCustomMoltProbility == FREE_PROB_MOLT  )
      {
		for (int l=1; l<=nclass;l++) 
		 molt_probability_in(h,igrow,l) = Grwth(icnt+l-1);
	    icnt += (nclass);
      } 
	}
   // high grade factors
   log_high_grade.initialize();
   int fleet; int sex; int year;
   for (int i=1;i<=NumAsympRet;i++)
    {
     fleet = AsympSel_fleet(i);
     sex = AsympSel_sex(i);
     year = AsympSel_year(i);
     log_high_grade(fleet,sex,year) = log(1.0-Asymret(i));
    }
   // m_dev parameters
   for (int I = 1; I <=nMdev-nSizeDevs; I++)
    {
     if (Mdev_spec(I) >=0)
      m_dev(I) = m_dev_est(I);
     else
      m_dev(I) = m_dev_est(-Mdev_spec(I));
     if (I <= nMdev_par_cnt(1))
      { m_dev_sex(1,I) =  m_dev(I); }
     else
      { m_dev_sex(2,I-nMdev_par_cnt(1)) =  m_dev(I); }
    }
   // M multiplier
   for (int l=1;l<=nclass;l++) Mmult(l) = 1;
   if (nSizeDevs >= 1)
    for (int ii=1;ii<=nSizeDevs;ii++)                                ///> Loop over changes in size
     for (int l = m_size_nodeyear(ii);l <= nclass; l++)
      Mmult(l) = m_dev_est(nMdev-nSizeDevs+ii);
  /**
   * @brief Instantiate and initialize selectivities for each gear as an array of pointers.
   * @author William Stockhausen
   * @details Selectivity "functions" are handled as classes. The class for each 
   * non-mirrored selectivity function is instantiated once here (called in the PRELIMINARY_CALCS_SECTION), 
   * and a pointer to it is saved to an array of pointers. Hopefully this will speed up calculating the selectivities
   * in the PROCEDURE_SECTION.
   *
   * Psuedocode:
   *  -# Loop over each gear:
   *  -# Create a pointer array with length = number of blocks
   *  -# Based on slx_type, fill pointer with parameter estimates.
   *  -# save the pointer to an array of pointers (ppSLX).
   *
   * Need to deprecate the abstract class for selectivity, 7X slower. (??)
  **/
}

void model_parameters::init_selectivities(void)
{
  int h,k, k2;
  dvar_vector pv;
  dvar_vector temp_slx1(1,nclass);
  dvariable p1, p2, p3, p4;
  //create pointer array
  if (ppSLX){
      for (int k=0;k<nslx;k++) delete ppSLX[k];
      delete ppSLX; ppSLX=0;
  }
  ppSLX = new class gsm::Selex<dvar_vector>*[nslx];
  // Specify non-mirrored selectivity
  class gsm::Selex<dvar_vector> *pSLX;
  int j = 1;
  for ( int k = 1; k <= nslx; k++ )
   if (slx_type(k) < 0) {ppSLX[k-1]=0; j++;} else
   {
    //class gsm::Selex<dvar_vector> *pSLX;
    dvar_vector temp_slx2(1,slx_extra(k));
    dvar_vector knots(1,slx_extra(k));
    switch ( slx_type(k) )
     {
      case SELEX_PARAMETRIC:                               ///> parametric
       for (int i = 1; i <= nclass; i++) { temp_slx1(i) = log_slx_pars(j); j++; }
       pv = temp_slx1;
       pSLX = new class gsm::ParameterPerClass<dvar_vector>(pv);
       break;
      case SELEX_COEFFICIENTS:                             ///> coefficients
       for (int i = 1; i <= slx_extra(k); i++) { temp_slx2(i) = log_slx_pars(j); j++; }
       pSLX = new class gsm::SelectivityCoefficients<dvar_vector>(temp_slx2);
       break;
      case SELEX_STANLOGISTIC:                             ///> logistic
       p1 = mfexp(log_slx_pars(j));
       j++;
       p2 = mfexp(log_slx_pars(j));
       j++;
       pSLX = new class gsm::LogisticCurve<dvar_vector,dvariable>(p1,p2);
       break;
      case SELEX_5095LOGISTIC:                             ///> logistic95
        p1 = mfexp(log_slx_pars(j));
        j++;
        p2 = mfexp(log_slx_pars(j));
        j++;
        pSLX = new class gsm::LogisticCurve95<dvar_vector,dvariable>(p1,p2);
      break;
      case SELEX_DECLLOGISTIC:                             ///> declining logistic
        p1 = mfexp(log_slx_pars(j));
        j++;
        p2 = mfexp(log_slx_pars(j));
        j++;
        for (int i = 1; i <= slx_extra(k); i++) { temp_slx2(i) = log_slx_pars(j); j++; }
        pSLX = new class gsm::DeclineLogistic<dvar_vector,dvariable,dvariable,dvar_vector>(p1,p2,temp_slx2);
      break;
      case SELEX_DOUBLENORM:                               ///> double normal
       p1 = mfexp(log_slx_pars(j));
       j++;
       p2 = mfexp(log_slx_pars(j));
       j++;
       p3 = mfexp(log_slx_pars(j));
       j++;
       pSLX = new class gsm::DoubleNormal<dvar_vector,dvariable>(p1,p2,p3);
       break;
      case SELEX_DOUBLENORM4:                               ///> double normal4
       p1 = mfexp(log_slx_pars(j));
       j++;
       p2 = mfexp(log_slx_pars(j));
       j++;
       p3 = mfexp(log_slx_pars(j));
       j++;
       p4 = mfexp(log_slx_pars(j));
       j++;
       pSLX = new class gsm::DoubleNormal4<dvar_vector,dvariable>(p1,p2,p3,p4);
       break;
      case SELEX_UNIFORM1:                                  ///> uniform 1
       pSLX = new class gsm::UniformCurve<dvar_vector>;
       break;
      case SELEX_UNIFORM0:                                  ///> uniform 0
       pSLX = new class gsm::Uniform0Curve<dvar_vector>;
       break;
      case SELEX_CUBIC_SPLINE:                             ///> cubic spline
       if (verbose>3) cout<<"creating SelectivitySpline class"<<endl;
       for (int i = 1; i <= slx_extra(k); i++) { knots(i) = mfexp(log_slx_pars_init(j)); j++; }
       for (int i = 1; i <= slx_extra(k); i++) { temp_slx2(i) = log_slx_pars(j); j++; }
       // Buck
       //need to set y_vals and x_vals below appropriately
       //y_vals are values at knots (a dvar_vector)
       //x_vals are knots           (a dvar_vector)
       pSLX = new class gsm::SelectivitySpline<dvar_vector,dvar_vector>(temp_slx2,knots);
       break;
     } // switch
     ppSLX[k-1] = pSLX;//save pointer to the instantiated selectivity object
   } //k
  /**
   * @brief Calculate selectivies for each gear.
   * @author Steve Martell, D'Arcy N. Webber
   * @details Three selectivities must be accounted for by each fleet.
   * 1) capture probability, 2) retention probability, and 3) release/discard probability.
   * Only the parameters for capture probability and retention probability are estimated.
   * The discard probability is calculated from these two probabilities.
   *
   * Maintain the possibility of estimating selectivity independently for each sex; assumes there are data to estimate female selex.
   *
   * Psuedocode:
   *  -# Loop over each gear:
   *  -# Create a pointer array with length = number of blocks
   *  -# Based on slx_type, fill pointer with parameter estimates.
   *  -# Loop over years and block-in the log_selectivity at mid points.
   *
   * Need to deprecate the abstract class for selectivity, 7X slower.
  **/
}

void model_parameters::calc_selectivities(void)
{
  int h,i,k, k2;
  dvar_vector pv;
  dvar_vector temp_slx1(1,nclass);
  dvariable p1, p2, p3, p4;
  log_slx_capture.initialize();
  log_slx_discard.initialize();
  log_slx_retaind.initialize();
  class gsm::Selex<dvar_vector> *pSLX;
  // Specify non-mirrored selectivity
  int j = 1;
  for ( int k = 1; k <= nslx; k++ )
   if (slx_type(k) < 0) {pSLX=0; j++;} else
   //if (slx_type(k) >= 0)
   {
     if (verbose>3) cout<<"retrieving selex for k = "<<k<<endl;
    dvar_vector temp_slx2(1,slx_extra(k));
    dvar_vector knots(1,slx_extra(k));
    switch ( slx_type(k) )
     {
      case SELEX_PARAMETRIC:                               ///> parametric
          if (verbose>3) cout<<"SELEX_PARAMETRIC"<<endl;
       for (i = 1; i <= nclass; i++) { temp_slx1(i) = log_slx_pars(j); j++; }
       ((gsm::ParameterPerClass<dvar_vector>*) ppSLX[k-1])->SetSelparms(temp_slx1);
       pSLX = ppSLX[k-1];
       break;
      case SELEX_COEFFICIENTS:                             ///> coefficients
          if (verbose>3) cout<<"SELEX_COEFFICIENTS"<<endl;
       for (i = 1; i <= slx_extra(k); i++) { temp_slx2(i) = log_slx_pars(j); j++; }
       ((gsm::SelectivityCoefficients<dvar_vector>*)ppSLX[k-1])->SetSelCoeffs(temp_slx2);
       pSLX = ppSLX[k-1];
       break;
      case SELEX_STANLOGISTIC:                             ///> logistic
          if (verbose>3) cout<<"SELEX_LOGISTIC95"<<endl;
       p1 = mfexp(log_slx_pars(j));
       j++;
       p2 = mfexp(log_slx_pars(j));
       j++;
       ((gsm::LogisticCurve<dvar_vector,dvariable>*) ppSLX[k-1])->SetParams(p1,p2);
       pSLX = ppSLX[k-1];
       break;
      case SELEX_5095LOGISTIC:                             ///> logistic95
          if (verbose>3) cout<<"SELEX_LOGISTIC95"<<endl;
        p1 = mfexp(log_slx_pars(j));
        j++;
        p2 = mfexp(log_slx_pars(j));
        j++;
       ((gsm::LogisticCurve95<dvar_vector,dvariable>*) ppSLX[k-1])->SetParams(p1,p2);
       pSLX = ppSLX[k-1];
      break;
      case SELEX_DECLLOGISTIC:                             ///> declining logistic
          if (verbose>3) cout<<"SELEX_DECLOGISTIC"<<endl;
        p1 = mfexp(log_slx_pars(j));
        j++;
        p2 = mfexp(log_slx_pars(j));
        j++;
        for (i = 1; i <= slx_extra(k); i++) { temp_slx2(i) = log_slx_pars(j); j++; }
       ((gsm::DeclineLogistic<dvar_vector,dvariable,dvariable,dvar_vector>*) ppSLX[k-1])->SetParams(p1,p2,temp_slx2);
       pSLX = ppSLX[k-1];
      break;
      case SELEX_DOUBLENORM:                               ///> double normal
          if (verbose>3) cout<<"SELEX_DOUBLENORM"<<endl;
       p1 = mfexp(log_slx_pars(j));
       j++;
       p2 = mfexp(log_slx_pars(j));
       j++;
       p3 = mfexp(log_slx_pars(j));
       j++;
       ((gsm::DoubleNormal<dvar_vector,dvariable>*) ppSLX[k-1])->SetParams(p1,p2,p3);
       pSLX = ppSLX[k-1];
       break;
      case SELEX_DOUBLENORM4:                               ///> double normal4
          if (verbose>3) cout<<"SELEX_DOUBLENORM4"<<endl;
       p1 = mfexp(log_slx_pars(j));
       j++;
       p2 = mfexp(log_slx_pars(j));
       j++;
       p3 = mfexp(log_slx_pars(j));
       j++;
       p4 = mfexp(log_slx_pars(j));
       j++;
       ((gsm::DoubleNormal4<dvar_vector,dvariable>*) ppSLX[k-1])->SetParams(p1,p2,p3,p4);
       pSLX = ppSLX[k-1];
       break;
      case SELEX_UNIFORM1: // uniform 1
          if (verbose>3) cout<<"SELEX_UNIFORM1"<<endl;
       pSLX = ppSLX[k-1];//gsm::UniformCurve<dvar_vector>
       break;
      case SELEX_UNIFORM0: // uniform 0
          if (verbose>3) cout<<"SELEX_UNIFORM0"<<endl;
       pSLX = ppSLX[k-1];//gsm::Uniform0Curve<dvar_vector>
       break;
      case SELEX_CUBIC_SPLINE:                             ///> coefficients
       if (verbose>3) cout<<"creating SelectivitySpline class"<<endl;
       for (int i = 1; i <= slx_extra(k); i++) { knots(i) = mfexp(log_slx_pars_init(j)); j++; }
       for (int i = 1; i <= slx_extra(k); i++) { temp_slx2(i) = log_slx_pars(j); j++; }
       // Buck
       //need to set y_vals and x_vals below appropriately
       //y_vals are values at knots (a dvar_vector)
       //x_vals are knots           (a dvar_vector)
       ((gsm::SelectivitySpline<dvar_vector,dvar_vector>*) ppSLX[k-1])->initSpline(temp_slx2,knots);
       pSLX = ppSLX[k-1];//gsm::SelectivitySpline<dvar_vector,dvar_vector>(temp_slx2,knots);
       //break;
     } //switch
    if (verbose>3) cout<<"done selecting SLX"<<endl;
    int h1 = 1;
    int h2 = nsex;
    if ( slx_isex(k) == MALESANDCOMBINED ) { h2 = MALESANDCOMBINED; }     ///> males (or combined sex) only
    if ( slx_isex(k) == FEMALES ) { h1 = FEMALES; }                       ///> females only
    for ( h = h1; h <= h2; h++ )
     {
      for ( i = slx_styr(k); i <= slx_edyr(k); i++ )
       {
        int kk = abs(slx_gear(k));                                        ///> fleet index (negative for retention)
        if ( slx_gear(k) > 0 )                                            ///> capture selectvity
         {
          log_slx_capture(kk,h,i) = pSLX->logSelectivity(dvar_mid_points);
          if (slx_type(k)==SELEX_PARAMETRIC || slx_type(k)==SELEX_COEFFICIENTS || slx_type(k)==SELEX_STANLOGISTIC || slx_type(k)==SELEX_5095LOGISTIC)
			if( slx_max_at_1(k) == 1)
             log_slx_capture(kk,h,i) -= log_slx_capture(kk,h,i,nclass);
          //cout << kk << " " << h << " " << i << " " << slx_type(k) << " " << log_slx_capture(kk,h,i) << " " << exp(log_slx_capture(kk,h,i)) << endl;
         }
        else                                                              ///> discard (because the gear is NEGATIVE)
         {
          log_slx_retaind(kk,h,i) = pSLX->logSelectivity(dvar_mid_points);
          if (slx_type(k)==SELEX_STANLOGISTIC || slx_type(k)==SELEX_5095LOGISTIC)
           log_slx_retaind(kk,h,i) -= log_slx_retaind(kk,h,i,nclass);
          log_slx_retaind(kk,h,i) += log_high_grade(kk,h,i);
          log_slx_discard(kk,h,i) = log(1.0 - exp(log_slx_retaind(kk,h,i)) + TINY);
          //cout << kk << " " << h << " " << i << " " << slx_type(k) << " " << log_slx_retaind(kk,h,i) << endl;
         }
       }
     }
    //do NOT "delete pSLX;"
   } // k
  // Mirror mirrow in the file  
  for ( int k = 1; k <= nslx; k++ )
   if (slx_type(k) < 0)
    {
     int kk = abs(slx_gear(k));                                        ///> fleet index (negative for retention)
     int h1 = 1;
     int h2 = nsex;
     if ( slx_isex(k) == MALESANDCOMBINED ) { h2 = MALESANDCOMBINED; }     ///> males (or combined sex) only
     if ( slx_isex(k) == FEMALES ) { h1 = FEMALES; }                       ///> females only
     if ( slx_gear(k) > 0 )                                              ///> capture selectvity
      {
       for ( i = syr; i <= nyrRetro; i++ )
        for ( h = h1; h <= h2; h++ ) 
         log_slx_capture(kk,h,i) = log_slx_capture(-slx_type(k),h,i);
      }
     else
      {
       for ( i = syr; i <= nyrRetro; i++ )
        for ( h = h1; h <= h2; h++ ) 
         { 
          log_slx_retaind(kk,h,i) = log_slx_retaind(-slx_type(k),h,i);
          log_slx_discard(kk,h,i) = log_slx_discard(-slx_type(k),h,i);
         } 
     }
    }
  // Sometimes one selectivity pattern is embedded in another
  for ( int k = 1; k <= nslx; k++ )
   if (slx_incl(k) > 0 & slx_gear(k) > 0)                                 ///> only for capture selectivity
    {
     int h1 = 1;
     int h2 = nsex;
     if ( slx_isex(k) == MALESANDCOMBINED ) { h2 = MALESANDCOMBINED; }    ///> males (and combined) only
     if ( slx_isex(k) == FEMALES ) { h1 = FEMALES; }                      ///> females only
     for ( h = h1; h <= h2; h++ )
      {
       int kk = abs(slx_gear(k));                                         ///> pointer to the fleet
       k2 = slx_incl(k);                                                  ///> pointer to the fleet within within which this fleet falls
       for ( i = slx_styr(k); i <= slx_edyr(k); i++ )
        for (int j=1;j<=nclass;j++) log_slx_capture(kk,h,i,j) += log_slx_capture(k2,h,i,j);
      }
    }
  /**
   * @brief Calculate fishing mortality rates for each fleet.
   * @details For each fleet estimate scaler log_fbar and deviates (f_devs). This function calculates the fishing mortality rate including deaths due to discards. Where xi is the discard mortality rate.
   *
   * In the event that there is effort data and catch data, then it's possible to estimate a catchability coefficient and predict the catch for the period of missing catch/discard data.  Best option for this would be to use F = q*E, where q = F/E.  Then in the objective function, minimize the variance in the estimates of q, and use the mean q to predict catch. Or minimize the first difference and assume a random walk in q.
   *
   * @param log_fbar are the mean fishing mortality of males parameters with dimension (1,nfleet,f_phz)
   * @param log_fdev are the male fdevs parameters with dimension (1,nfleet,1,nFparams,f_phz)
   * @param log_foff are the offset to the male fishing mortality parameters with dimension (1,nfleet,foff_phz)
   * @param log_fdov are the female fdev offset parameters with dimension (1,nfleet,1,nYparams,foff_phz)
   * @param dmr is the discard mortality rate
   * @param F is the fishing mortality with dimension (1,nsex,syr,nyr,1,nseason,1,nclass)
  **/
}

void model_parameters::calc_fishing_mortality(void)
{
  int ik,yk;
  double xi; // discard mortality rate
  dvar_vector sel(1,nclass);
  dvar_vector ret(1,nclass);
  dvar_vector vul(1,nclass);
  // Initilaize F2 with 1.0e-10
  F.initialize();
  dvariable log_ftmp;
   for ( int h = 1; h <= nsex; h++ )
    for ( int i = syr; i <= nyrRetro; i++ )
     for ( int j = 1; j <= nseason; j++ )
      for ( int l = 1; l <= nclass; l++)
       F2(h,i,j,l) = 1.0e-10;
  // fishing morrtality generally
  ft.initialize(); fout.initialize();
  for ( int k = 1; k <= nfleet; k++ )
   for ( int h = 1; h <= nsex; h++ )
    {
     ik = 1; yk = 1;
     for ( int i = syr; i <= nyrRetro; i++ )
      for ( int j = 1; j <= nseason; j++ )
       {
        if ( fhit(i,j,k)>0 )
         {
          log_ftmp = log_fbar(k) + log_fdev(k,ik++);                 ///> Male F is the reference plus the annual deviation
          fout(k,i) = exp(log_ftmp);                                 ///> Report of male F
          if (h==2) log_ftmp += log_foff(k);                         ///> Female F is an offset from male F
          if (h==2 & yhit(i,j,k)>0) log_ftmp += log_fdov(k,yk++);    ///> annual F dev
          ft(k,h,i,j) = mfexp(log_ftmp);
          xi  = dmr(i,k);                                            ///> Discard mortality rate
          sel = mfexp(log_slx_capture(k,h,i))+1.0e-10;               ///> Capture selectivity
          ret = mfexp(log_slx_retaind(k,h,i)) * slx_nret(h,k);       ///> Retension
          vul = elem_prod(sel, ret + (1.0 - ret) * xi);              ///> Vulnerability
          F(h,i,j) += ft(k,h,i,j) * vul;                             ///> Fishing mortality  
          F2(h,i,j) += ft(k,h,i,j) * sel;                            ///> Contact mortality
         }
       } // years and seasons
    } // fleet and sex
  /**
   * @brief Calculate natural mortality array
   * @details Natural mortality (M) is a 3d array for sex, year and size.
   *
   * todo: Size-dependent mortality
  **/
}

void model_parameters::calc_natural_mortality(void)
{
  // reset M by sex, year and time
  M.initialize();
  // Add random walk to natural mortality rate
  dvar_vector delta(syr+1,nyrRetro);
  // Sex
  for( int m = 1; m <= nmature; m++)
  for (int h=1;h<=nsex;h++)
   {
    M(h,m) = M0(h);
	// adjusts for maturity specific natural mortality (immature gets a multplier)
    if(m_maturity==1 & m==2)
	 M(h,m) = M0(h) * mfexp(m_mat_mult(h));
    delta.initialize();
    switch( m_type )
     {
      // case 0 (M_CONSTANT) not here as this is not evaluated if m_dev is not active
      case M_RANDOM:                                         ///> random walk in natural mortality
       for (int iy=syr+1;iy<=nyrRetro;iy++) delta(iy) = m_dev_sex(h,iy)-m_dev_sex(h,iy-1);
       break;
      case M_CUBIC_SPLINE:                                   ///> cubic splines
       {
        dvector iyr = (m_nodeyear_sex(h) - syr) / (nyrRetro - syr);
        dvector jyr(syr+1,nyrRetro);
        jyr.fill_seqadd(0, 1.0 / (nyrRetro - syr - 1));
        vcubic_spline_function csf(iyr, m_dev_sex(1));
        delta = csf(jyr);
       }
       break;
      case M_BLOCKED_CHANGES:                                ///> Specific break points
     for ( int idev = 1; idev <= nMdev_par_cnt(h); idev++ )
      delta(m_nodeyear_sex(1,idev)) = m_dev_sex(h,idev);
     break;
    // Modifying by Jie Zheng for specific time blocks
    case M_TIME_BLOCKS1: // time blocks
     for ( int idev = 1; idev <= nMdev_par_cnt(h); idev++ )
      {
       // Is this syntax for split sex?
       for ( int i = m_nodeyear_sex(h,1+(idev-1)*2); i <= m_nodeyear_sex(h,2+(idev-1)*2); i++ )
        M(h,m)(i) = mfexp(m_dev_sex(h,idev));
      }
     break;
    // Case for specific years
    case M_TIME_BLOCKS3: // time blocks
     for ( int idev = 1; idev <= nMdev_par_cnt(h); idev++ ) delta(m_nodeyear_sex(h,idev)) = m_dev_sex(1,idev);
     for ( int i = syr+1; i <= nyrRetro; i++ )
       M(h,m)(h) = M(h,m)(syr) * mfexp(delta(i)); // Deltas are devs from base value (not a walk)
     break;
    case M_TIME_BLOCKS2: // time blocks
     for ( int idev = 1; idev <= nMdev_par_cnt(h)-1; idev++ )
      {
       for ( int i = m_nodeyear_sex(h,idev); i < m_nodeyear_sex(h,idev+1); i++ )
         M(h,m)(i) = M(h,m)(i)*mfexp(m_dev_sex(h,idev));
      }
     break;
    }
   // Update M by year.
   if ( m_type < 4 )
    for ( int i = syr+1; i <= nyrRetro; i++ ) M(h,m)(i) = M(h,m)(i-1) * mfexp(delta(i));
   for (int i = syr; i <= nyrRetro; i++)                                  ///> Account for size-specific M
    for (int l=1;l<=nclass;l++)  M(h,m,i,l) *= Mmult(l);
  }
  /**
   * @brief Calculate total instantaneous mortality rate and survival rate
   * @details \f$ S = exp(-Z) \f$
   *
   * ISSUE, for some reason the diagonal of S goes to NAN if linear growth model is used. Due to F.
   *
   * @param m_prop is a vector specifying the proportion of natural mortality (M) to be applied each season
   * @return NULL
  **/
}

void model_parameters::calc_total_mortality(void)
{
  Z.initialize(); Z2.initialize();S.initialize();
 for( int m = 1; m <= nmature; m++)
  for ( int h = 1; h <= nsex; h++ )
   for ( int i = syr; i <= nyrRetro; i++ )
    for ( int j = 1; j <= nseason; j++ )
     {
      Z(h,m,i,j) = m_prop(i,j) * M(h,m,i) + F(h,i,j);
      Z2(h,m,i,j) = m_prop(i,j) * M(h,m,i) + F2(h,i,j);
      if (season_type(j) == 0) for ( int l = 1; l <= nclass; l++ ) S(h,m,i,j)(l,l) = 1.0-Z(h,m,i,j,l)/Z2(h,m,i,j,l)*(1.0-mfexp(-Z2(h,m,i,j,l)));
      if (season_type(j) == 1) for ( int l = 1; l <= nclass; l++ ) S(h,m,i,j)(l,l) = mfexp(-Z(h,m,i,j,l));
     }
  /**
   * @brief Calculate the probability of moulting by carapace width.
   * @details Note that the parameters molt_mu and molt_cv can only be estimated in cases where there is new shell and old shell data. Note that the diagonal of the P matrix != 0, otherwise the matrix is singular in inv(P).
   *
   * @param molt_mu is the mean of the distribution
   * @param molt_cv scales the variance of the distribution
  **/
}

void model_parameters::calc_molting_probability(void)
{
  double tiny = 0.000;
  molt_probability.initialize();
  for ( int h = 1; h <= nsex; h++ )
   for ( int igrow=1;igrow<=nMoltVaries(h);igrow++)
    {
     // Pre-specified molt probability
     if (bUseCustomMoltProbility==FIXED_PROB_MOLT)
      {
       for ( int i = syr; i <= nyrRetro; i++ )
        {
         if (igrow==1)
          molt_probability(h)(i) = CustomMoltProbabilityMatrix(h,1);
         else
          {
           if ( igrow > 1 && i >= iYrsMoltChanges(h,igrow-1))
            molt_probability(h)(i) = CustomMoltProbabilityMatrix(h,igrow);
          }
        }
      }
     // Uniform selectivity
     if (bUseCustomMoltProbility == CONSTANT_PROB_MOLT)
      {
       for ( int i = syr; i <= nyrRetro; i++ )
        for ( int l = 1; l <= nclass; l++ )
          molt_probability(h,i,l) = 1;
      }
     // Estimated logistic selectivity
     if (bUseCustomMoltProbility == LOGISTIC_PROB_MOLT)
      {
       dvariable mu = molt_mu(h,1);
       dvariable sd = mu * molt_cv(h,1);
       for ( int i = syr; i <= nyrRetro; i++ )
        {
         if ( igrow > 1 && i >= iYrsMoltChanges(h,igrow-1) )
          {
           mu = molt_mu(h,igrow);
           sd = mu * molt_cv(h,igrow);
          }
         molt_probability(h)(i) = 1.0 - ((1.0 - 2.0 * tiny) * plogis(dvar_mid_points, mu, sd) + tiny);
        }
      }
	  // Estimated free probability of molting
	  if (bUseCustomMoltProbility==FREE_PROB_MOLT)
      {
       for ( int i = syr; i <= nyr; i++ )
        {
         if (igrow==1)
          molt_probability(h)(i) = molt_probability_in(h,1);
         else
          {
           if ( igrow > 1 && i >= iYrsMoltChanges(h,igrow-1))
            molt_probability(h)(i) = molt_probability_in(h,igrow);
          }
        }
      }
    }
  /**
   * @brief Compute growth increments
   * @details Presently based on liner form
   *
   * @param vSizes is a vector of doubles of size data from which to compute predicted values
   * @param iSex is an integer vector indexing sex (1 = male, 2 = female)
   *
   * @return dvar_vector of predicted growth increments
  **/
}

dvar_vector model_parameters::calc_growth_increments(const dvector vSizes, const ivector iSex)
{
  {
   if ( vSizes.indexmin() != iSex.indexmin() || vSizes.indexmax() != iSex.indexmax() )
    { cerr << "indices don't match..." << endl; ad_exit(1); }
    RETURN_ARRAYS_INCREMENT();
    dvar_vector pMoltInc(1,vSizes.indexmax());
    pMoltInc.initialize();
    int h,i;
    for ( i = 1; i <= nGrowthObs; i++ )
     {
      h = iSex(i);
      pMoltInc(i) = alpha(h) - beta(h) * vSizes(i);
     }
    RETURN_ARRAYS_DECREMENT();
    return pMoltInc;
  }
  /**
   * @brief Molt increment as a linear function of pre-molt size.
   *
   * TODO: Option for empirical molt increments.
   *
   * @param alpha
   * @param beta
   * @param mid_points
   *
   * @return molt_increment
  **/
}

void model_parameters::calc_growth_increments(void)
{
  if (bUseGrowthIncrementModel==LINEAR_GROWTHMODEL)
   for ( int h = 1; h <= nsex; h++ )
    for ( int l = 1; l <= nclass; l++ )
     molt_increment(h,1,l) = alpha(h) - beta(h) * mid_points(l);
  /**
   * @brief Calclate the growth and size transtion matrix
   * @details Calculates the size transition matrix for each sex based on growth increments, which is a linear function of the size interval, and the scale parameter for the gamma distribution.  This function does the proper integration from the lower to upper size bin, where the mode of the growth increment is scaled by the scale parameter.
   *
   * This function loops over sex, then loops over the rows of the size transition matrix for each sex.  The probability of transitioning from size l to size ll is based on the vector molt_increment and the scale parameter. In all there are three parameters that define the size transition matrix (alpha, beta, scale) for each sex. Issue 112 details some of evolution of code development here
   *
   * @param gscale
   * @param P a 3D array of molting probabilities with dimension (1,nsex,1,nclass,1,nclass)
  **/
}

void model_parameters::calc_growth_transition(void)
{
  int count68;
  dvariable mean_size_after_molt;
  dvariable Accum,CumInc,Upper_Inc;
  dvar_vector psi(1,nclass+1);
  dvar_vector sbi(1,nclass+1);
  dvar_matrix gt(1,nclass,1,nclass);
  dvariable Len1Low,Len1Hi,Len2Low,Len2Hi,total,step,prob_val,l1r;
  dvariable mlk,sigmaK2,l1,rangL,rangU,Upp1,Kr,kval,temp,temp6,scale;
  dvariable mll,sigmaL2,Linfval,Linfr,LinfU,LinfL,temp2,temp4,temp5;
  dvariable templ11,templ12,temp68,tempr,nvar,tempL1,tempL2,tempk1,tempk2;
  dvariable Temp,Val,Cum;
  dvar_vector prob_val_vec(1,1024);
  // reset the growth transition matrix
  growth_transition.initialize();
  // loop over sex
  for ( int h = 1; h <= nsex; h++ )
   {
    //  Set the growth-transition matrix (does not include molt_probability)
    if ( bUseCustomGrowthMatrix == GROWTH_FIXEDGROWTHTRANS || bUseCustomGrowthMatrix == GROWTH_FIXEDSIZETRANS)
     for (int j=1;j<=nSizeIncVaries(h);j++) growth_transition(h,j) = CustomGrowthMatrix(h,j);
    // Set the growth-transition matrix (size-increment is gamma)
    if ( bUseCustomGrowthMatrix == GROWTH_INCGAMMA )
     {
      for (int k =1; k<=nSizeIncVaries(h);k++)
       {
        gt.initialize();
        for ( int l = 1; l <= nSizeSex(h)-1; l++ )
         {
          mean_size_after_molt =  (molt_increment(h,k,l))/ gscale(h,k);
          Accum = 0;
          for ( int ll = l; ll <= nSizeSex(h)-1; ll++ )
           {
            Upper_Inc = (size_breaks(ll+1) - mid_points(l))/gscale(h,k);
            CumInc = cumd_gamma(Upper_Inc, mean_size_after_molt);
            gt(l,ll) = CumInc - Accum;
            Accum = CumInc;
           }
          gt(l,nSizeSex(h)) = 1.0 - Accum;
         }
        gt(nSizeSex(h),nSizeSex(h)) = 1.0;
        growth_transition(h,k) = gt;
       }
     }
    // Set the growth-transition matrix (size after increment is gamma)
    if ( bUseCustomGrowthMatrix == GROWTH_SIZEGAMMA )
     {
      for (int k =1; k<=nSizeIncVaries(h);k++)
       {
        gt.initialize();
        sbi = size_breaks / gscale(h,k);
        for ( int l = 1; l <= nSizeSex(h); l++ )
         {
          mean_size_after_molt = (mid_points(l) + molt_increment(h,k,l)) / gscale(h,k);
          psi.initialize();
          for (int ll = l; ll <= nclass+1; ll++ )
           psi(ll) = cumd_gamma(sbi(ll), mean_size_after_molt);
          gt(l)(l,nSizeSex(h)) = first_difference(psi(l,nclass+1));
          gt(l)(l,nSizeSex(h)) = gt(l)(l,nSizeSex(h)) / sum(gt(l));
         }
        growth_transition(h,k) = gt;
       }
     }
    // Set the growth-transition matrix (size after increment is normal)
    if ( bUseCustomGrowthMatrix == GROWTH_NORMAL )
     {
      for (int k =1; k<=nSizeIncVaries(h);k++)
       {
        gt.initialize();
        sbi = size_breaks / gscale(h,k);
        for ( int l = 1; l <= nSizeSex(h)-1; l++ )
         {
          mean_size_after_molt = mid_points(l) + molt_increment(h,k,l);
          Temp = 0;
          for ( int ll = l; ll <= nclass-1; ll++ )
           {
            Val = (size_breaks(ll+1) - mean_size_after_molt)/gscale(h,k);
            Cum = cumd_norm(Val);
            gt(l)(ll) = Cum - Temp;
            Temp = Cum;
           }
          gt(l,nclass) = 1.0-Temp;
         }
        gt(nclass,nclass) = 1.0;
        growth_transition(h,k) = gt;
       }
     }
    // set the growth matrix based inidvidual variation in kappa
    if ( bUseCustomGrowthMatrix == GROWTH_VARYK )
     {
      for (int k =1; k<=nSizeIncVaries(h);k++)
       {
        mlk = log(Kappa(h,k));
        sigmaK2 = SigmaKappa(h,k)*SigmaKappa(h,k);
        tempk2 = sqrt(2.0*M_PI*sigmaK2);
        growth_transition(h,k,nSizeSex(h),nSizeSex(h)) = 1;               // No growth from the last class
        // the initial size class
        for (int l = 1; l <= nSizeSex(h)-1; l++ )
         {
          Len1Low = size_breaks(l); Len1Hi = size_breaks(l+1);
          scale = 1.0/(Len1Hi-Len1Low);
          temp = Len1Low; total = 0;
          if (Len1Low < Linf(h,k))
           {
            for(int l2c=l;l2c<=nSizeSex(h)+20;l2c++)
             {
              if (l2c<=nSizeSex(h))
               step = size_breaks(l2c+1)-size_breaks(l2c);
              else
               step = size_breaks(nSizeSex(h)+1)-size_breaks(nSizeSex(h));
              l1r = step/2.0;
              Len2Low = temp;  Len2Hi = temp + step; temp = Len2Hi;
              prob_val = 0;
              for(int evl1=1;evl1<=32;evl1++)
               {
                l1 = ((xg(evl1) + 1.0)/2.0)*(Len1Hi-Len1Low) + Len1Low;
                if (Linf(h,k) <= Len2Hi) Upp1 = Linf(h,k) - l1 - 0.001; else Upp1 = Len2Hi - l1;
                rangU = -log(1 - Upp1/(Linf(h,k) - l1));
                if(Linf(h,k) > Len2Low)
                 {
                  rangL = -log(1 - (Len2Low - l1)/(Linf(h,k) - l1));
                  Kr = (rangU-rangL)/2.0;
                  for( int evk=1; evk<=32;evk++)
                   {
                    kval = ((xg(evk) + 1.0)/2.0)*(rangU-rangL) + rangL;
                    if(kval > 0)
                     {
                      temp6 = mfexp(-((log(kval) - mlk)*(log(kval) - mlk))/(2.0*sigmaK2))/(kval*tempk2);
                      prob_val += Kr*wg(evk)*temp6*wg(evl1)*scale;
                     }
                   } // evk
                 } //if(Linf > Len2Low)
               } // evl1
              prob_val *= l1r;
              total += prob_val;
              if(l2c < nSizeSex(h))
               growth_transition(h,k,l,l2c) = prob_val;
              else
               growth_transition(h,k,l,nSizeSex(h)) += prob_val;
             } // l2c
            for(int l2c=l;l2c<=nSizeSex(h);l2c++) growth_transition(h,k,l,l2c) /= total;
           } // if (LenLow < Linf)
          else
           {
            growth_transition(h,k,l,l) = 1;
            total = 1;
           }
         } // l
       } // k
     } // if
     // Linf varies among individuals
     if ( bUseCustomGrowthMatrix == GROWTH_VARYLINF )
      {
       for (int k =1; k<=nSizeIncVaries(h);k++)
        {
         mll = log(Linf(h,k));
         sigmaL2 = SigmaLinf(h,k)*SigmaLinf(h,k);
         tempL1 = sqrt(2.0*M_PI*sigmaL2);
         growth_transition(h,k,nSizeSex(h),nSizeSex(h)) = 1;               // No growth from the last class
         // the initial size class
         for ( int l = 1; l <= nSizeSex(h)-1; l++ )
          {
           Len1Low = size_breaks(l); Len1Hi = size_breaks(l+1);
           scale = 1.0/(Len1Hi-Len1Low);
           temp = Len1Low; total = 0;
           for(int l2c=l;l2c<=nSizeSex(h)+10;l2c++)
            {
             if (l2c<=nSizeSex(h))
              step = size_breaks(l2c+1)-size_breaks(l2c);
             else
              step = size_breaks(nSizeSex(h)+1)-size_breaks(nSizeSex(h));
             l1r = step/2.0;
             Len2Low = temp;  Len2Hi = temp + step; temp = Len2Hi;
             prob_val = 0;
             for(int evl1=1;evl1<=32;evl1++)
              {
               l1 = ((xg(evl1) + 1.0)/2.0)*(Len1Hi-Len1Low) + Len1Low;
               LinfU = l1 + (Len2Hi - l1)/(1-mfexp(-Kappa(h,k)));
               if(l2c == l) LinfL = l1; else LinfL = l1 + (Len2Low - l1)/(1-mfexp(-Kappa(h,k)));
               temp2 = (log(l1) - mll)/SigmaLinf(h,k);
               temp4 = 1.0 - cumd_norm(temp2);
               Linfr = (LinfU - LinfL)/2.0;
               for(int evL=1; evL<=32;evL++)
                {
                 Linfval = ((xg(evL) + 1.0)/2.0)*(LinfU - LinfL) + LinfL;
                 temp5 = 1.0/(Linfval*tempL1)*mfexp(-((log(Linfval) - mll)*(log(Linfval) - mll))/(2*sigmaL2));
                 prob_val += Linfr*wg(evL)*temp5*wg(evl1)*scale/temp4;
                } // evl
               } // evl1
             prob_val *= l1r;
             total += prob_val;
             if(l2c < nSizeSex(h))
               growth_transition(h,k,l,l2c) = prob_val;
             else
              growth_transition(h,k,l,nSizeSex(h)) += prob_val;
            } // l2c
           for(int l2c=l;l2c<=nSizeSex(h);l2c++) growth_transition(h,k,l,l2c) /= total;
          } // l
        } // k
      }  // if
     // Linf and K vary among individuals
     if ( bUseCustomGrowthMatrix == GROWTH_VARYKLINF )
      {
       for (int k =1; k<=nSizeIncVaries(h);k++)
        {
         nvar = 15;
         mll = log(Linf(h,k));
         mlk = log(Kappa(h,k));
         sigmaK2 = SigmaKappa(h,k)*SigmaKappa(h,k);
         sigmaL2 = SigmaLinf(h,k)*SigmaLinf(h,k);
         tempL1 = sqrt(2.0*M_PI*sigmaL2);
         tempL2 = 2.0*sigmaL2;
         tempk1 = sqrt(2.0*M_PI*sigmaK2);
         tempk2 = 2.0*sigmaK2;
         temp = sqrt(mfexp(2.0*mlk+sigmaK2)*(mfexp(sigmaK2)-1.0))*nvar;
         rangU = Kappa(h,k) + temp;
         rangL = Kappa(h,k) - temp;
         if(rangL < 0) rangL = 0;
         Kr = (rangU - rangL)/2.0;
         growth_transition(h,k,nSizeSex(h),nSizeSex(h)) = 1;               // No growth from the last class
         // the initial size class
         for ( int l = 1; l <= nSizeSex(h)-1; l++ )
          {
           Len1Low = size_breaks(l); Len1Hi = size_breaks(l+1);
           temp = Len1Low; total = 0;
           scale = 1.0/(Len1Low-Len1Hi);
           for(int l2c=l;l2c<=nSizeSex(h)+20;l2c++)
            {
             if (l2c<=nSizeSex(h))
              step = size_breaks(l2c+1)-size_breaks(l2c);
             else
              step = size_breaks(nSizeSex(h)+1)-size_breaks(nSizeSex(h));
             l1r = step/2.0;
             templ11 = scale*Kr*l1r;
             Len2Low = temp;  Len2Hi = temp + step; temp = Len2Hi; prob_val = 0;
             for(int evl1=1;evl1<=32;evl1++)
              {
               l1 = l1_vec(h,l,evl1);
               temp2 = (log(l1) - mll)/SigmaLinf(h,k);
               temp4 = 1.0 - cumd_norm(temp2);
               templ12 = wg(evl1)*templ11/temp4;
               count68 = 1;
               for( int evk=1;evk<=32;evk++)
                {
                 kval = ((xg(evk) + 1.0)/2.0)*(rangU-rangL) + rangL;
                 LinfU = l1 + (Len2Hi - l1)/(1.0-mfexp(-kval));
                 if(l2c == l) LinfL = l1; else LinfL = l1 + (Len2Low - l1)/(1-mfexp(-kval));
                 Linfr = (LinfU - LinfL)/2.0;
                 temp6 = mfexp(-((log(kval) - mlk)*(log(kval) - mlk))/tempk2)/(kval*tempk1);
                 temp68 = wg(evk)*temp6*templ12;
                 for(int evL=1;evL<=32;++evL)
                  {
                   Linfval = ((xg(evL) + 1.0)/2.0)*(LinfU - LinfL) + LinfL;
                   temp5 = mfexp(-((log(Linfval) - mll)*(log(Linfval) - mll))/tempL2)/(Linfval*tempL1);
                   prob_val_vec(count68) = Linfr*wg(evL)*temp5*temp68;
                   count68 += 1;
                  }
                }
               prob_val += sum(prob_val_vec);
              }
             total += prob_val;
             if(l2c < nSizeSex(h))
              growth_transition(h,k,l,l2c) = prob_val;
             else
              growth_transition(h,k,l,nSizeSex(h)) += prob_val;
            } // l2c
           for(int l2c=l;l2c<=nSizeSex(h);l2c++) growth_transition(h,k,l,l2c) /= total;
          } // l
        } // k
      }  // if
   } // h
  /**
   * @brief calculate size distribution for new recuits.
   * @details Based on the gamma distribution, calculates the probability of a new recruit being in size-interval size.
   *
   * @param ra is the mean of the distribution
   * @param rbeta scales the variance of the distribution
   * @return rec_sdd the recruitment size distribution vector
  **/
}

void model_parameters::calc_recruitment_size_distribution(void)
{
  dvariable ralpha;
  dvar_vector x(1,nclass+1);
  rec_sdd.initialize();
  for ( int h=1; h <=nsex; h++)
   {
    ralpha = ra(h) / rbeta(h);
    for ( int l = 1; l <= nclass+1; l++ )  x(l) = cumd_gamma(size_breaks(l) / rbeta(h), ralpha);
    rec_sdd(h) = first_difference(x);
    for (int l=nSizeClassRec(h)+1;l<=nclass;l++) rec_sdd(h,l) = 0;
    rec_sdd(h) /= sum(rec_sdd(h)); // Standardize so each row sums to 1.0
   }
   // snow crab way CSS change back when done comparing 
   // for ( int h=1; h <=nsex; h++)
   // {
    // ralpha = ra(h) / rbeta(h);
    // for ( int l = 1; l <= 6; l++ )  
     // rec_sdd(h,l) = pow(size_breaks(l)+2.5-size_breaks(1),ralpha-1)*mfexp(-(size_breaks(l)+2.5-size_breaks(1))/rbeta(h));
	// rec_sdd(h) /= sum(rec_sdd(h)); // Standardize so each row sums to 1.0
   // }
  /**
   * @brief initialiaze populations numbers-at-length in syr
   * @author Steve Martell
   * @details This function initializes the populations numbers-at-length in the initial year of the model.
   *
   * Psuedocode: See note from Dave Fournier.
   *
   * For the initial numbers-at-length a vector of deviates is estimated, one for each size class, and have the option to initialize the model at unfished equilibrium, or some other steady state condition.
   *
   *  Dec 11, 2014. Martell & Ianelli at snowgoose.  We had a discussion regarding how to deal with the joint probability of molting and growing to a new size
   *  interval for a given length, and the probability of not molting.  We settled on using the size-tranistion matrix to represent this joint probability, where the diagonal of the matrix to represent the probability of surviving and molting to a new size interval. The upper diagonal of the size-transition matrix represent the probability of growing to size interval j' given size interval j.
   *
   *  Oldshell crabs are then the column vector of 1-molt_probabiltiy times the numbers-at-length, and the Newshell crabs is the column vector of molt_probability times the number-at-length.
   *
   *  Jan 1, 2015.  Changed how the equilibrium calculation is done. Use a numerical approach to solve the newshell oldshell initial abundance.
   *
   *  Jan 3, 2015.  Working with John Levitt on analytical solution instead of the numerical approach.  Think we have a soln.
   *
   *  Notation:
   *      n = vector of newshell crabs
   *      o = vector of oldshell crabs
   *      P = diagonal matrix of molting probabilities by size
   *      S = diagonal matrix of survival rates by size
   *      A = Size transition matrix.
   *      r = vector of new recruits (newshell)
   *      I = identity matrix.
   *
   *  The following equations represent the dynamics of newshell and oldshell crabs.
   *      n = nSPA + oSPA + r                     (1)
   *      o = oS(I-P)A + nS(I-P)A                 (2)
   *  Objective is to solve the above equations for n and o repsectively. Starting with o:
   *      o = n(I-P)S[I-(I-P)S]^(-1)              (3)
   *  next substitute (3) into (1) and solve for n
   *      n = nPSA + n(I-P)S[I-(I-P)S]^(-1)PSA + r
   *  let B = [I-(I-P)S]^(-1)
   *      n - nPSA - n(I-P)SBPSA = r
   *      n(I - PSA - (I-P)SBPSA) = r
   *  let C = (I - PSA - (I-P)SBPSA)
   *  then n = C^(-1) r                           (4)
   *
   *  April 28, 2015. There is no case here for initializing the model at unfished equilibrium conditions. Need to fix this for SRA purposes. SJDM.
   *
   * @param bInitializeUnfished
   * @param logR0
   * @param logRini
   * @param rec_sdd is the vector of recruitment size proportions. It has dimension (1,nclass)
   * @param rec_ini is the vector of initial size deviations. It has dimension (1,nclass)
   * @param M is a 3D array of the natural mortality. It has dimension (1,nsex,syr,nyrRetro,1,nclass)
   * @param S is a 5D array of the survival rate (where S=exp(-Z)). It has dimension (1,nsex,syr,nyrRetro,1,nseason,1,nclass,1,nclass)
   * @param d4_N is the numbers in each group (sex/maturity/shell), year, season and length. It has dimension (1,n_grp,syr,nyrRetro+1,1,nseason,1,nclass)
  **/
}

void model_parameters::calc_initial_numbers_at_length(void)
{
  dvariable log_initial_recruits, scale;
  // Reset the probability of molting to first year value
  ProbMolt.initialize();
  for (int h = 1; h <= nsex; h++ )
   for (int l=1;l<=nclass;l++)
    ProbMolt(h,l,l) = molt_probability(h,syr,l);
  // Initial recruitment
  switch( bInitializeUnfished )
   {
    case UNFISHEDEQN:                                      ///> Unfished conditions
      log_initial_recruits = logR0;
      break;
    case FISHEDEQN:                                        ///> Steady-state fished conditions
      log_initial_recruits = logRini;
      break;
    case FREEPARS:                                         //> Free parameters
      log_initial_recruits = logN0(1,1);
      break;
    case FREEPARSSCALED:                                   ///> Free parameters revised
      log_initial_recruits = logRini;
      break;
   }
  for ( int h = 1; h <= nsex; h++ )
   { recruits(h)(syr) = mfexp(log_initial_recruits); }
  // Analytical equilibrium soln
  int ig;
  d4_N.initialize();
  dmatrix Id = identity_matrix(1,nclass);
  dvar_matrix  x(1,n_grp,1,nclass);
  dvar_vector  y(1,nclass);
  dvar_matrix  A(1,nclass,1,nclass);
  dvar_matrix _S(1,nclass,1,nclass);
  _S.initialize();
  Eqn_basis = CONSTANTREC;                                ///> Need to run brute force with constant recruitment
  switch( bInitializeUnfished )
   {
    case UNFISHEDEQN:                                     ///> Unfished conditions
     bSteadyState = UNFISHEDEQN;
     for (int k=1;k<=nfleet;k++) log_fimpbar(k) = -100;
     x = calc_brute_equilibrium(syr,syr,syr,200);
     for ( int ig = 1; ig <= n_grp; ig++ ) d4_N(ig)(syr)(1) = x(ig);
     break;
    case FISHEDEQN:                                       ///> Steady-state fished conditions
     bSteadyState = FISHEDEQN;
     for (int k=1;k<=nfleet;k++) log_fimpbar(k) = log(finit(k)+1.0e-10);
     x = calc_brute_equilibrium(syr,syr,syr,200);
     for ( int ig = 1; ig <= n_grp; ig++ ) d4_N(ig)(syr)(1) = x(ig);
     break;
    case FREEPARS:                                        ///> Free parameters
     // Single shell condition and sex
     for ( int h = 1; h <= nsex; h++ )
      for ( int m = 1; m <= nmature; m++ )
       for ( int o = 1; o <= nshell; o++ )
        {
         int ig = pntr_hmo(h,m,o);
         d4_N(ig)(syr)(1) = mfexp(logN0(ig));
        }
     break;
    case FREEPARSSCALED:                                 ///> Free parameters (revised
     scale = sum(exp(logN0));
     for ( int h = 1; h <= nsex; h++ )
      for ( int m = 1; m <= nmature; m++ )
       for ( int o = 1; o <= nshell; o++ )
        {
         int ig = pntr_hmo(h,m,o);
         d4_N(ig)(syr)(1) = mfexp(log_initial_recruits+logN0(ig))/scale;
        }
     break;
   }
  /**
   * @brief Update numbers-at-length
   * @author Team
   * @details Numbers at length are propagated each year for each sex based on the size transition matrix and a vector of size-specifc survival rates. The columns of the size-transition matrix are multiplied by the size-specific survival rate (a scalar). New recruits are added based on the estimated average recruitment and annual deviate, multiplied by a vector of size-proportions (rec_sdd).
   *
   * @param bInitializeUnfished
   * @param logR0
   * @param logRbar
   * @param d4_N is the numbers in each group (sex/maturity/shell), year, season and length. It has dimension (1,n_grp,syr,nyrRetro+1,1,nseason,1,nclass)
   * @param recruits is the vector of average recruits each year. It has dimension (syr,nyrRetro)
   * @param rec_dev is an init_bounded_dev_vector of recruitment deviation parameters. It has dimension (syr+1,nyrRetro,-7.0,7.0,rdv_phz)
   * @param rec_sdd is the vector of recruitment size proportions. It has dimension (1,nclass)
  **/
}

void model_parameters::update_population_numbers_at_length(void)
{
  int h,i,ig,o,m,isizeTrans;
  dmatrix Id = identity_matrix(1,nclass);
  dvar_vector rt(1,nclass);
  dvar_vector  x(1,nclass);
  dvar_vector  y(1,nclass);
  dvar_vector  z(1,nclass);
  // this is what should be used because recruitment is not always during the first season (i.e. during the initial conditions)
  for ( i = syr; i <= nyrRetro; i++ )
   for ( h = 1; h <= nsex; h++ )
    {
     if ( bInitializeUnfished == UNFISHEDEQN )
      recruits(h,i) = mfexp(logR0)*float(nsex);
     else
      recruits(h,i) = mfexp(logRbar)*float(nsex);
     // This splits recruitment out proportionately into males and females
     if (h == MALESANDCOMBINED) recruits(h)(i) *= mfexp(rec_dev(i)) * 1.0 / (1.0 + mfexp(-logit_rec_prop(i)));
     if (h == FEMALES) recruits(h)(i) *= mfexp(rec_dev(i)) * (1.0 - 1.0 / (1.0 + mfexp(-logit_rec_prop(i))));
    }
  for ( i = syr; i <= nyrRetro; i++ )
   for ( int j = 1; j <= nseason; j++ )
    {
     for ( ig = 1; ig <= n_grp; ig++ )
      {
       h = isex(ig);
       isizeTrans = iYrIncChanges(h,i);
       m = imature(ig);
       o = ishell(ig);
       x = d4_N(ig)(i)(j);
       // Mortality (natural and fishing)
       x = x * S(h,m)(i)(j);
       if ( nshell == 1 )
        {
		if(nmature == 1)
		 {
		 // Molting and growth
         if (j == season_growth)
           {
            y = elem_prod(x, 1.0 - molt_probability(h)(i)); // did not molt, 
            x = elem_prod(x, molt_probability(h)(i)) * growth_transition(h,isizeTrans); // molted and grew, 
            x = x + y;
           }
         // Recruitment
         if (j == season_recruitment) x += recruits(h)(i) * rec_sdd(h);
         if (j == nseason) d4_N(ig)(i+1)(1) = x;  else  d4_N(ig)(i)(j+1) = x;
		 }
        if(nmature == 2)
		 {
		  if ( m == 1 ) // mature
          {
           //No molting, growth, or recruitment for mature animals
           if (j == nseason) d4_N(ig)(i+1)(1) = x; else  d4_N(ig)(i)(j+1) = x;
          }
          if ( m == 2 ) // immature
          {
          // Molting and growth
           z.initialize();
           if (j == season_growth)
            {
             //z = elem_prod(x, molt_probability(h)(i)) * growth_transition(h,isizeTrans); 		// molted to maturity
             //x = elem_prod(x, 1 - molt_probability(h)(i)) * growth_transition(h,isizeTrans);    // molted, but immature
			 z = elem_prod(x * growth_transition(h,isizeTrans), molt_probability(h)(i)) ; 		// molted to maturity
             x = elem_prod(x * growth_transition(h,isizeTrans), 1 - molt_probability(h)(i)) ;    // molted, but immature
            }
		   if (j == season_recruitment) x += recruits(h)(i) * rec_sdd(h);
           if (j == nseason)
            { d4_N(ig-1)(i+1)(1) += z; d4_N(ig)(i+1)(1) = x; }
            else
            { d4_N(ig-1)(i)(j+1) += z; d4_N(ig)(i)(j+1) = x; }
          }	 
		 }
        }
       else
        {
         if ( o == 1 ) // newshell
          {
          // Molting and growth
           if (j == season_growth)
            {
             y = elem_prod(x, 1.0 - molt_probability(h)(i)); // did not molt, become oldshell
             x = elem_prod(x, molt_probability(h)(i)) * growth_transition(h,isizeTrans); // molted and grew, stay newshell
            }
           //Recruitment
           if (j == season_recruitment) x += recruits(h)(i) * rec_sdd(h);
           if (j == nseason) d4_N(ig)(i+1)(1) = x; else  d4_N(ig)(i)(j+1) = x;
          }
         if ( o == 2 ) // oldshell
          {
          //Molting and growth
           z.initialize();
           if (j == season_growth)
            {
             z = elem_prod(x, molt_probability(h)(i)) * growth_transition(h,isizeTrans); // molted and grew, become newshell
             x = elem_prod(x, 1 - molt_probability(h)(i)) + y; // did not molt, remain oldshell and add the newshell that become oldshell
            }
           if (j == nseason)
            { d4_N(ig-1)(i+1)(1) += z; d4_N(ig)(i+1)(1) = x; }
            else
            { d4_N(ig-1)(i)(j+1) += z; d4_N(ig)(i)(j+1) = x; }
          }
        }
	} // ig
  } // i and j
  /**
   * @brief Calculate predicted catch observations
   * @details The function uses the Baranov catch equation to predict the retained and discarded catch.
   *
   * Assumptions:
   *  1) retained (landed catch) is assume to be newshell male only.
   *  2) discards are all females (new and old) and male only crab.
   *  3) Natural and fishing mortality occur simultaneously.
   *  4) discard is the total number of crab caught and discarded.
  **/
}

void model_parameters::calc_predicted_catch(void)
{
  int nhit;                                                          ///> number of values for computing q
  double cobs, effort;                                               ///> used when computing q
  dvariable tmp_ft,totalnalobs,totalnalpre;                          ///> temp variables
  dvar_vector sel(1,nclass);                                         ///> capture selectivity
  dvar_vector nal(1,nclass);                                         ///> numbers or biomass at length.
  dvar_vector tempZ1(1,nclass);                                      ///> total mortality
  // First need to calculate a catchability (q) for each catch data frame if there is any catch and effort (must be both)
  log_q_catch.initialize();
  for ( int kk = 1; kk <= nCatchDF; kk++ )
   {
    nhit = 0;
    for ( int jj = 1; jj <= nCatchRows(kk); jj++ )
     if (dCatchData(kk,jj,1) <= nyrRetro)
      {
       cobs =   obs_catch(kk,jj);                                     ///> catch data
       effort = dCatchData(kk,jj,10);                                 ///> Effort data
       if (cobs > 0.0 && effort > 0.0)                                ///> There are catch and effort data
        {
         int i    =     dCatchData(kk,jj,1);                          ///> year index
         int j    =     dCatchData(kk,jj,2);                          ///> season index
         int k    =     dCatchData(kk,jj,3);                          ///> fleet/gear index
         int h    =     dCatchData(kk,jj,4);                          ///> sex index
         int type = int(dCatchData(kk,jj,7));                         ///> Type of catch (total= 0, retained = 1, discard = 2)
         int unit = int(dCatchData(kk,jj,8));                         ///> Units of catch equation (1 = biomass, 2 = numbers)
         if ( h != BOTHSEX )                                          ///> sex specific
          {
           log_q_catch(kk) += log(ft(k,h,i,j) / effort);
           nhit += 1;
          }
         else // sexes combinded
          {
           totalnalobs = 0; totalnalpre = 0;
           for ( h = 1; h <= nsex; h++ )
            {
             sel = log_slx_capture(k,h,i);                            ///> Capture seletiity
             switch( type )
              {
               case RETAINED: // retained catch
                sel = mfexp(sel + log_slx_retaind(k,h,i));
                break;
               case DISCARDED: // discarded catch
                sel = elem_prod(mfexp(sel), 1.0 - mfexp(log_slx_retaind(k,h,i)));
                break;
               case TOTALCATCH: // total catch
                sel = mfexp(sel);
                break;
               }
             nal.initialize();                                        ///> Computer numbers
             for ( int m = 1; m <= nmature; m++ )
              for ( int o = 1; o <= nshell; o++ )
               { 
		        int ig = pntr_hmo(h,m,o); 
			    nal = d4_N(ig,i,j); 
                nal = (unit == 1) ? elem_prod(nal, mean_wt(h,i)) : nal;
                tmp_ft = ft(k,h,i,j);
                if (season_type(j)==INSTANT_F) tempZ1 = Z2(h,m,i,j); else tempZ1 = Z(h,m,i,j);
                totalnalobs += nal * elem_div(elem_prod(tmp_ft * sel, 1.0 - mfexp(-tempZ1)), tempZ1);
                totalnalpre += nal * elem_div(elem_prod(effort * sel, 1.0 - mfexp(-tempZ1)), tempZ1);
			}
            }
           log_q_catch(kk) += log(totalnalobs / totalnalpre);
           nhit += 1;
          } // h
        } // cobs
      } // jj
    if ( nhit > 0 ) log_q_catch(kk) /= nhit;
   }
  // Now make predictions
  res_catch.initialize();
  pre_catch.initialize();
  obs_catch_effort.initialize();
  for ( int kk = 1; kk <= nCatchDF; kk++ )
   {
    for ( int jj = 1; jj <= nCatchRows(kk); jj++ )
     if (dCatchData(kk,jj,1) <= nyrRetro)
      {
       int i    =     dCatchData(kk,jj,1);                            ///> year index
       int j    =     dCatchData(kk,jj,2);                            ///> season index
       int k    =     dCatchData(kk,jj,3);                            ///> fleet/gear index
       int h    =     dCatchData(kk,jj,4);                            ///> sex index
       int type = int(dCatchData(kk,jj,7));                           ///> Type of catch (total= 0, retained = 1, discard = 2)
       int unit = int(dCatchData(kk,jj,8));                           ///> Units of catch equation (1 = biomass, 2 = numbers)
       effort   =     dCatchData(kk,jj,10);                           ///> Effort data
       cobs     =        obs_catch(kk,jj);                            ///> catch data
       if ( h!=BOTHSEX ) // sex specific
        {
         sel = log_slx_capture(k,h,i);                                ///> Capture selectivity
         //ret = log_slx_retaind(k,h,i);                                ///> Retention probability
         //dis = log_slx_discard(k,h,i);                                ///> Discard fraction
         switch ( type )
          {
           case RETAINED:                                             ///> retained catch
            sel = mfexp(sel + log_slx_retaind(k,h,i));
            break;
           case DISCARDED:                                            ///> discarded catch
            sel = elem_prod(mfexp(sel), 1.0 - mfexp(log_slx_retaind(k,h,i)));
            break;
           case TOTALCATCH:                                           ///> total catch
            sel = mfexp(sel);
            break;
          }
         // sum of nals
         nal.initialize();                                            ///> Computer numbers
         for ( int m = 1; m <= nmature; m++ )
          for ( int o = 1; o <= nshell; o++ )
           { 
	        int ig = pntr_hmo(h,m,o); 
			 nal = d4_N(ig,i,j); 
             nal = (unit == 1) ? elem_prod(nal, mean_wt(h,i)) : nal;
            if (season_type(j)==INSTANT_F) tempZ1 = Z2(h,m,i,j); else tempZ1 = Z(h,m,i,j);
			// predict catch
			tmp_ft = ft(k,h,i,j);                                       /// > Extract F
			pre_catch(kk,jj) += nal * elem_div(elem_prod(tmp_ft * sel, 1.0 - mfexp(-tempZ1)), tempZ1);
			if (cobs == 0 & effort > 0.0)
			obs_catch_effort(kk,jj) += nal * elem_div(elem_prod(mfexp(log_q_catch(kk)) * effort * sel, 1.0 - mfexp(-tempZ1)), tempZ1);
			}
		}
       else  // sexes combined
        {
         for ( h = 1; h <= nsex; h++ )
          {
           sel = log_slx_capture(k)(h)(i);
           switch( type )
            {
             case RETAINED: // retained catch
              sel = mfexp(sel + log_slx_retaind(k,h,i));
              break;
             case DISCARDED: // discarded catch
              sel = elem_prod(mfexp(sel), 1.0 - mfexp(log_slx_retaind(k,h,i)));
              break;
             case TOTALCATCH: // total catch
              sel = mfexp(sel);
              break;
             }
           // sum of nals
           nal.initialize();
           for ( int m = 1; m <= nmature; m++ )
            for ( int o = 1; o <= nshell; o++ )
             { 
		      int ig = pntr_hmo(h,m,o);
			  nal = d4_N(ig,i,j); 
              nal = (unit == 1) ? elem_prod(nal, mean_wt(h,i)) : nal;
			 tmp_ft = ft(k,h,i,j);                                      /// > Extract F
			 if (season_type(j)==INSTANT_F) tempZ1 = Z2(h,m,i,j); else tempZ1 = Z(h,m,i,j);
			 pre_catch(kk,jj) += nal * elem_div(elem_prod(tmp_ft * sel, 1.0 - mfexp(-tempZ1)), tempZ1);
			 if (cobs == 0 & effort > 0.0)
				obs_catch_effort(kk,jj) +=  nal * elem_div(elem_prod(mfexp(log_q_catch(kk)) * effort * sel, 1.0 - mfexp(-tempZ1)), tempZ1);
            }
		  }
        } // sex-specific
       // Catch residuals
       // In first case (obs_catch > 0) then if there is only catch data, calculate the residual as per usual; if there is catch and effort data, then still use observed catch to calculate the residual, despite the predicted catch being calculated differently.
       // In second case, when effort > 0 then the residual is the pred catch using Fs - pred catch using q
       if ( obs_catch(kk,jj) > 0.0 )
        {
         res_catch(kk,jj) = log(obs_catch(kk,jj)) - log(pre_catch(kk,jj));
        }
       else
        if (effort > 0.0)
         {
          res_catch(kk,jj) = log(obs_catch_effort(kk,jj)) - log(pre_catch(kk,jj));
         }
      } // lines of catch
   } // data block
  /**
   * @brief Calculate predicted catch for a combination of years
   * @author Andre Punt
   * @details The function uses the Baranov catch equation to predict the retained, discarded, or total catch
   * year i; season j; sex h; gear k; type (1=retained;2=discards;3=total); unit (1=mass;2=numbers)
  **/
}

dvariable model_parameters::calc_predicted_catch_det(const int i, const int j, const int h, const int k, const int type, const int unit)
{
 {
  dvariable tmp_ft,out;
  dvar_vector sel(1,nclass);                                         ///> capture selectivity
  dvar_vector nal(1,nclass);                                         ///> numbers or biomass at length.
  dvar_vector tempZ1(1,nclass);                                      ///> total mortality
  nal.initialize();
  sel = log_slx_capture(k,h,i);
  switch( type )
    {
     case RETAINED: // retained catch
      sel = mfexp(sel + log_slx_retaind(k,h,i));
      break;
     case DISCARDED: // discarded catch
      sel = elem_prod(mfexp(sel), 1.0 - mfexp(log_slx_retaind(k,h,i)));
      break;
     case TOTALCATCH: // total catch
      sel = mfexp(sel);
      break;
    }
  nal.initialize();
  out.initialize();
  for ( int m = 1; m <= nmature; m++ )
   for ( int o = 1; o <= nshell; o++ )
    { 
	int ig = pntr_hmo(h,m,o);
	nal = d4_N(ig,i,j); 
	nal = (unit == 1) ? elem_prod(nal, mean_wt(h,i)) : nal;
	tmp_ft = ft(k,h,i,j);                                              /// > Extract F
	if (season_type(j) == INSTANT_F) tempZ1 = Z2(h,m,i,j); else tempZ1 = Z(h,m,i,j);
	out += nal * elem_div(elem_prod(tmp_ft * sel, 1.0 - mfexp(-tempZ1)), tempZ1);
	}
  return(out);
 }
  /**
   * @brief Calculate predicted catch for all years (not just data years)
   * @author D'Arcy N. Webber
   * @details The function uses the Baranov catch equation to predict the retained and discarded catch for all model years (not just those years for which we have observations). This is used for plotting purposes only.
  **/
}

void model_parameters::calc_predicted_catch_out(void)
{
  dvariable tmp_ft,out2;
  dvar_vector sel(1,nclass);                                         ///> capture selectivity
  dvar_vector nal(1,nclass);                                         ///> numbers or biomass at length.
  dvar_vector tempZ1(1,nclass);                                      ///> total mortality
  pre_catch_out.initialize();
  for ( int i = syr; i <= nyrRetro; i++ )
   {
    for ( int kk = 1; kk <= nCatchDF; kk++ )
     {
      int j    =     dCatchData_out(kk,i,2);                         ///> season index
      int k    =     dCatchData_out(kk,i,3);                         ///> fleet/gear index
      int h    =     dCatchData_out(kk,i,4);                         ///> sex index
      int type = int(dCatchData_out(kk,i,7));                        ///> Type of catch (total= 0, retained = 1, discard = 2)
      int unit = int(dCatchData_out(kk,i,8));                        ///> Units of catch equation (1 = biomass, 2 = numbers)
      if ( h != BOTHSEX )                                            ///> sex specific
       {
        sel = log_slx_capture(k,h,i);
        switch ( type )
         {
          case RETAINED: // retained catch
           sel = mfexp(sel + log_slx_retaind(k,h,i));
           break;
          case DISCARDED: // discarded catch
           sel = elem_prod(mfexp(sel), 1.0 - mfexp(log_slx_retaind(k,h,i)));
           break;
          case TOTALCATCH: // total catch
           sel = mfexp(sel);
           break;
         }
        nal.initialize();
        for ( int m = 1; m <= nmature; m++ )
         for ( int o = 1; o <= nshell; o++ )
          { 
			int ig = pntr_hmo(h,m,o); 
			nal = d4_N(ig,i,j); 
			tmp_ft = ft(k,h,i,j);
			nal = (unit == 1) ? elem_prod(nal, mean_wt(h,i)) : nal;
			if (season_type(j)==INSTANT_F) tempZ1 = Z2(h,m,i,j); else tempZ1 = Z(h,m,i,j)+1.0e-10;
			pre_catch_out(kk,i) += nal * elem_div(elem_prod(tmp_ft * sel, 1.0 - mfexp(-tempZ1)), tempZ1);
	      }
       }
      else
       {
        // sexes combined
        out2 = 0;
        for ( int h = 1; h <= nsex; h++ )
         {
          sel = log_slx_capture(k)(h)(i);
          switch( type )
           {
            case RETAINED: // retained catch
             sel = mfexp(sel + log_slx_retaind(k)(h)(i));
             break;
            case DISCARDED: // discarded catch
             sel = elem_prod(mfexp(sel), 1.0 - mfexp(log_slx_retaind(k)(h)(i)));
             break;
            case TOTALCATCH: // total catch
             sel = mfexp(sel);
             break;
           }
          nal.initialize();
          for ( int m = 1; m <= nmature; m++ )
           for ( int o = 1; o <= nshell; o++ )
            {
				int ig = pntr_hmo(h,m,o);
				nal = d4_N(ig,i,j); 
				nal = (unit == 1) ? elem_prod(nal, mean_wt(h,i)) : nal;
				tmp_ft = ft(k,h,i,j);
				if (season_type(j)==INSTANT_F) tempZ1 = Z2(h,m,i,j); else tempZ1 = Z(h,m,i,j);
					pre_catch_out(kk,i) += nal * elem_div(elem_prod(tmp_ft * sel, 1.0 - mfexp(-tempZ1)), tempZ1);
			}
          //out2 += calc_predicted_catch_det(i, j, h, k, type, unit);
         } // h
       } // sex
     } // kk
    } // i
  res_catch_out.initialize();
  for ( int kk = 1; kk <= nCatchDF; kk++ )
   for ( int i = syr; i <= nyrRetro; i++ )
    if ( obs_catch_out(kk,i) > 0.0 && pre_catch_out(kk,i) > 0.0 )
     res_catch_out(kk,i) = log(obs_catch_out(kk,i)) - log(pre_catch_out(kk,i));          ///> Catch residuals
  /**
   * @brief Calculate predicted relative abundance and residuals
   * @author Steve Martell, D'Arcy Webber
   *
   * @details This function uses the conditional mle for q to scale the population to the relative abundance index. Assumed errors in relative abundance are lognormal.  Currently assumes that the CPUE index is made up of both retained and discarded crabs.
   *
   * Question regarding use of shell condition in the relative abundance index. Currenlty there is no shell condition information in the CPUE data, should there be? Similarly, there is no mature immature information, should there be?
  **/
}

void model_parameters::calc_relative_abundance(void)
{
  int unit;
  dvar_vector sel(1,nclass);                                         ///> capture selectivity
  dvar_vector nal(1,nclass);                                         ///> numbers or biomass at length.
  dvar_vector V(1,nSurveyRows);
  V.initialize();
  for ( int k = 1; k <= nSurveys; k++ )
   {
    for ( int jj = 1; jj <= nSurveyRows; jj++ )
     if (dSurveyData(jj,0) == k)
      if (dSurveyData(jj,1) <= nyrRetro || (dSurveyData(jj,1) == nyrRetro+1 & dSurveyData(jj,2) == 1))
       {
        nal.initialize();
        int i = dSurveyData(jj,1);                                     ///> year index
        int j = dSurveyData(jj,2);                                     ///> season index
        int g = dSurveyData(jj,3);                                     ///> fleet/gear index
        int h1 = dSurveyData(jj,4);                                    ///> sex index
        int m1 = dSurveyData(jj,5);                                    ///> maturity index
        int unit = dSurveyData(jj,8);                                  ///> units 1 = biomass 2 = numbers
		// ANDRES original code
        // for (int h = 1; h <= nsex; h++ )                               ///> Select sex
         // if (h==h1 || h== BOTHSEX)
          // for (int m = 1; m <= nmature; m++ )                          ///> Select maturity 
           // if (m==m1 || m1 == BOTHMATURE)
            // {
             // sel = mfexp(log_slx_capture(g)(h)(i));
             // for ( int o = 1; o <= nshell; o++ )
              // {
               // int ig = pntr_hmo(h,m,o);
               // nal += ( unit == 1 ) ? elem_prod(d4_N(ig,i,j), mean_wt(h,i)) : d4_N(ig,i,j);
              // }
             // V(jj) = nal * sel;
            // }
        // }  // nSurveyRows
		//=========================================================================
		//==============Calculate index for NO TERMINAL MOLT cases=================
		if(nmature == 1)
		{
		//=========maturity state is summed over in index============
		 if(m1 == 0)
          for (int h = 1; h <= nsex; h++ )                               ///> Select sex
           if (h==h1 || h== BOTHSEX)
            {
             sel = mfexp(log_slx_capture(g)(h)(i));
			 for ( int m = 1; m <= nmature; m++ )		//this doesn't really need to be here
              for ( int o = 1; o <= nshell; o++ )		
               {
                int ig = pntr_hmo(h,m,o);
                nal += ( unit == 1 ) ? elem_prod(d4_N(ig,i,j), mean_wt(h,i)) : d4_N(ig,i,j);
               }
             V(jj) = nal * sel;
            }
		//=========index is only MATURE crab============
		//===this uses an input maturity at size vector 
		 if(m1 == 1)
          for (int h = 1; h <= nsex; h++ )                               
           if (h==h1 || h== BOTHSEX)
            {
             sel = mfexp(log_slx_capture(g)(h)(i));
			 for ( int m = 1; m <= nmature; m++ )		//this doesn't really need to be here
              for ( int o = 1; o <= nshell; o++ )		//mature crab can be both old and new shell
               {
                int ig = pntr_hmo(h,m,o);
                nal += ( unit == 1 ) ? elem_prod(maturity(h),elem_prod(d4_N(ig,i,j), mean_wt(h,i))) : elem_prod(d4_N(ig,i,j),maturity(h));
               }
             V(jj) = nal * sel;
            }
		//=========insert case for immature only crab...if anyone would actually do this============  
         if(m1 ==2)
	    	{
				cout<<"there is no case for immature indices currently"<<endl;
				exit(1);
			}		
		}
		//==============================================================================
		//================calculate index for TERMINAL MOLT cases=======================
	    if(nmature == 2)
		{
		 //=========maturity state is summed over in index============
		 if(m1 == 0)
          for (int h = 1; h <= nsex; h++ )                               
           if (h==h1 || h== BOTHSEX)
            {
             sel = mfexp(log_slx_capture(g)(h)(i));
			 for ( int m = 1; m <= nmature; m++ )		
              for ( int o = 1; o <= nshell; o++ )		
               {
                int ig = pntr_hmo(h,m,o);
                nal += ( unit == 1 ) ? elem_prod(d4_N(ig,i,j), mean_wt(h,i)) : d4_N(ig,i,j);
               }
             V(jj) = nal * sel;
            }
	     //===only mature crab in index =================================
		 //==this uses the separate arrays for immature and mature crab
		 //==to calculate mature biomass--this is different than above
		 if(m1 == 1)
		  for (int h = 1; h <= nsex; h++ )                               
           if (h==h1 || h== BOTHSEX)
            {
             sel = mfexp(log_slx_capture(g)(h)(i));
			 for ( int m = 1; m <= 1; m++ )	
              for ( int o = 1; o <= nshell; o++ )		
               {
                int ig = pntr_hmo(h,m,o);
                nal += ( unit == 1 ) ? elem_prod(d4_N(ig,i,j), mean_wt(h,i)) : d4_N(ig,i,j);
               }
             V(jj) = nal * sel;
            }
	     //=========insert case for immature only crab...if anyone would actually do this============  
         if(m1 ==2)
		 {
			cout<<"there is no case for immature indices currently"<<endl;
			exit(1);
		 }	
		}
      }// nSurveyRows
    // Do we need an analystical Q
    if (q_anal(k) == 1)
     {
      dvariable zt; dvariable npnt; dvariable ztot;
      npnt = 0;
      ztot = 0;
      for ( int jj = 1; jj <= nSurveyRows; jj++ )
       if (dSurveyData(jj,0) == k)
        if (dSurveyData(jj,1) <= nyrRetro || (dSurveyData(jj,1) == nyrRetro+1 & dSurveyData(jj,2) == 1))
         {
          zt = log(obs_cpue(jj)) - log(V(jj));
          npnt += 1;
          ztot += zt;   
         }
       survey_q(k) = mfexp(ztot/npnt);
     }  
    for ( int jj = 1; jj <= nSurveyRows; jj++ )
    if (dSurveyData(jj,0) == k)
     if (dSurveyData(jj,1) <= nyrRetro || (dSurveyData(jj,1) == nyrRetro+1 & dSurveyData(jj,2) == 1))
      {
       pre_cpue(jj) = survey_q(k) * V(jj);
       res_cpue(jj) = log(obs_cpue(jj)) - log(pre_cpue(jj));
      }   
  } // surveys
  /**
   * @brief Calculate predicted size composition data.
   *
   * @details Predicted size composition data are given in proportions.
   * Size composition strata:
   *  - sex  (0 = both sexes, 1 = male, 2 = female)
   *  - type (0 = all catch, 1 = retained, 2 = discard)
   *  - shell condition (0 = all, 1 = new shell, 2 = oldshell)
   *  - mature or immature (0 = both, 1 = immature, 2 = mature)
   *
   *  Jan 5, 2015.
   *  Size compostion data can come in a number of forms.
   *  Given sex, maturity and 3 shell conditions, there are 12 possible
   *  combinations for adding up the numbers at length (nal).
   *
   *                          Shell
   *    Sex     Maturity        condition   Description
   *    _____________________________________________________________
   *    Male    0               1           immature, new shell
   * !  Male    0               2           immature, old shell
   * !  Male    0               0           immature, new & old shell               1               Male, immature, new shell
   *    Male    1               1             mature, new shell
   *    Male    1               2             mature, old shell
   *    Male    1               0             mature, new & old shell
   *  Female    0               1           immature, new shell
   * !Female    0               2           immature, old shell
   * !Female    0               0           immature, new & old shell
   *  Female    1               1             mature, new shell
   *  Female    1               2             mature, old shell
   *  Female    1               0             mature, new & old shell
   *    _____________________________________________________________
   *
   *  Call function to get the appropriate numbers-at-length.
   *
  **/
}

void model_parameters::calc_predicted_composition(void)
{
   dvar_vector dNtmp(1,nclass);                                      ///> temporary Ns
   dvar_vector nal(1,nclass);                                        ///> numbers or biomass at length.
   d3_pre_size_comps_in.initialize();
   d3_pre_size_comps.initialize();
   for ( int ii = 1; ii <= nSizeComps_in; ii++ )
    {
     int nbins = nSizeCompCols_in(ii);
     for ( int jj = 1; jj <= nSizeCompRows_in(ii); jj++ )
      if (d3_SizeComps_in(ii,jj,-7) <= nyrRetro || (d3_SizeComps_in(ii,jj,-7) == nyrRetro+1 & d3_SizeComps_in(ii,jj,-6) == 1) ) 
       {
        dNtmp.initialize();
        int i       = d3_SizeComps_in(ii)(jj,-7);                     ///> year
        int j       = d3_SizeComps_in(ii)(jj,-6);                     ///> seas
        int k       = d3_SizeComps_in(ii)(jj,-5);                     ///> gear (a.k.a. fleet)
        int h       = d3_SizeComps_in(ii)(jj,-4);                     ///> sex
        int type    = d3_SizeComps_in(ii)(jj,-3);                     ///> retained or discard
        int shell   = d3_SizeComps_in(ii)(jj,-2);                     ///> shell condition
        int bmature = d3_SizeComps_in(ii)(jj,-1);                     ///> boolean for maturity
        if ( h != BOTHSEX )                                           ///> sex specific
         {
          dvar_vector sel = mfexp(log_slx_capture(k,h,i));
          dvar_vector ret = mfexp(log_slx_retaind(k,h,i));
          dvar_vector dis = mfexp(log_slx_discard(k,h,i));
          nal.initialize();                                           ///> Numbers by sex
		  // need cases for when maturity changes and when shell condition changes
		  if(nmature == 1)
		  {
		   for ( int m = 1; m <= nmature; m++ )
		    for ( int o = 1; o <= nshell; o++ )
            {
             int ig = pntr_hmo(h,m,o);
             if ( shell == 0 ) nal += d4_N(ig,i,j);
             if ( shell == o ) nal += d4_N(ig,i,j);
            }
		  }
		  if(nmature == 2)
		  {
		   for ( int m = 1; m <= nmature; m++ )
		    for ( int o = 1; o <= nshell; o++ )
            {
             int ig = pntr_hmo(h,m,o);
             if ( bmature == 0 ) nal += d4_N(ig,i,j);
             if ( bmature == m ) nal += d4_N(ig,i,j);
            }
		  }
          switch ( type )
           {
            case RETAINED:                                            ///> retained
             dNtmp += elem_prod(nal, elem_prod(sel, ret));
            break;
            case DISCARDED:                                           ///> discarded
             dNtmp += elem_prod(nal, elem_prod(sel, dis));
            break;
            case TOTALCATCH:                                          ///> both retained and discarded
             dNtmp += elem_prod(nal, sel);
            break;
           }
         }
        else
         { // sexes combined in the observations
          for ( int h = 1; h <= nsex; h++ )
           {
            dvar_vector sel = mfexp(log_slx_capture(k,h,i));
            dvar_vector ret = mfexp(log_slx_retaind(k,h,i));
            dvar_vector dis = mfexp(log_slx_discard(k,h,i));
            nal.initialize();                                         ///> Numbers by sex
            for ( int m = 1; m <= nmature; m++ )
             for ( int o = 1; o <= nshell; o++ )
              {
               int ig = pntr_hmo(h,m,o);
               if ( shell == 0 ) nal += d4_N(ig,i,j);
               if ( shell == o ) nal += d4_N(ig,i,j);
              }
            switch ( type )
             {
              case RETAINED:                                          ///> retained
               dNtmp += elem_prod(nal, elem_prod(sel, ret));
              break;
              case DISCARDED:                                         ///> discarded
               dNtmp += elem_prod(nal, elem_prod(sel, dis));
              break;
              case TOTALCATCH:                                        ///> both retained and discarded
               dNtmp += elem_prod(nal, sel);
              break;
             }
           }
         }
        d3_pre_size_comps_in(ii)(jj)        = dNtmp(1,nbins);
        d3_pre_size_comps_in(ii)(jj)(nbins) = sum(dNtmp(nbins,nclass));
       }
    }
   // This aggregates the size composition data by appending size compositions horizontally
   int oldk = 9999; int j; int i;
   for ( int kk = 1; kk <= nSizeComps_in; kk++ )
    {
     int k = iCompAggregator(kk);
     if ( oldk != k ) j = 0;
     oldk = k;
     for ( int jj = 1; jj <= nSizeCompCols_in(kk); jj++ )
      {
       j += 1;
       for ( int ii = 1; ii <= nSizeCompRows_in(kk); ii++ )
        if (d3_SizeComps_in(kk,ii,-7) <= nyrRetro || (d3_SizeComps_in(kk,ii,-7) == nyrRetro+1 & d3_SizeComps_in(kk,ii,-6) == 1) )
        { i = ii; d3_pre_size_comps(k,i,j) = d3_pre_size_comps_in(kk,ii,jj); }
      }
    }
   // This normalizes all observations by row
   for ( int k = 1; k <= nSizeComps; k++ )
    for ( int i = 1; i <= nSizeCompRows(k); i++ )
     if (size_comp_year(k,i) <= nyrRetro || (size_comp_year(k,i) == nyrRetro+1 & size_comp_season(k,i) == 1) )
      d3_pre_size_comps(k,i) /= sum(d3_pre_size_comps(k,i));
  /**
   * @brief Calculate stock recruitment relationship.
   * @details  Assuming a Beverton-Holt relationship between the mature biomass (user defined) and the annual recruits. Note that we derive so and bb in R = so MB / (1 + bb * Mb) from Ro and steepness (leading parameters defined in theta).
   *
   * NOTES: if nSRR_flag == 1 then use a Beverton-Holt model to compute the recruitment deviations for minimization.
  **/
}

void model_parameters::calc_stock_recruitment_relationship(void)
{
  dvariable so, bb;
  dvariable ro = mfexp(logR0);
  dvariable phiB;
  double lam;
  dvariable reck = 4.*steepness/(1.-steepness);
  dvar_matrix _A(1,nclass,1,nclass);
  dvar_matrix _S(1,nclass,1,nclass);
  // Reset the probability of molting to first year value
  ProbMolt.initialize();
  for (int h = 1; h <= nsex; h++ )
   for (int l=1;l<=nclass;l++)
    ProbMolt(h,l,l) = molt_probability(h,syr,l);
  // get unfished mature male biomass per recruit.
  phiB = 0.0;
  _A.initialize();
  _S.initialize();
  for( int h = 1; h <= nsex; h++ )
   {
    for ( int l = 1; l <= nclass; ++l )  _S(l,l) = mfexp(-M(h,1)(syr)(l));
    _A = growth_transition(h,1);
    dvar_vector x(1,nclass);
    dvar_vector y(1,nclass);
    h <= 1 ? lam = spr_lambda: lam = (1.0 - spr_lambda);
    // Single shell condition
    if ( nshell == 1 && nmature == 1 )
     {
      calc_equilibrium(x,_A,_S,rec_sdd(h));
      phiB += lam * x * elem_prod(mean_wt(h)(syr), maturity(h));
     }
    // Continuous molt (newshell/oldshell)
    if ( nshell == 2 && nmature == 1 )
     {
      calc_equilibrium(x,y,_A,_S,ProbMolt(h),rec_sdd(h));
      phiB += lam * x * elem_prod(mean_wt(h)(syr), maturity(h)) +  lam * y * elem_prod(mean_wt(h)(syr), maturity(h));
     }
    // Insert terminal molt case here
  }
  dvariable bo = ro * phiB;
  so = reck * ro / bo;
  bb = (reck - 1.0) / bo;
  dvar_vector ssb = calc_ssb().shift(syr+1);
  dvar_vector rhat = elem_div(so * ssb , 1.0 + bb* ssb);
  // residuals
  int byr = syr + 1;
  res_recruit.initialize();
  dvariable sigR = mfexp(logSigmaR);
  dvariable sig2R = 0.5 * sigR * sigR;
  switch ( nSRR_flag )
   {
    case 0: // NO SRR
     res_recruit(byr,nyrRetro) = log(recruits(1)(byr,nyrRetro)) - (1.0-rho) * logRbar - rho * log(++recruits(1)(byr-1,nyrRetro-1)) + sig2R;
     break;
    case 1: // SRR model
     res_recruit(byr,nyrRetro) = log(recruits(1)(byr,nyrRetro)) - (1.0-rho) * log(rhat(byr,nyrRetro)) - rho * log(++recruits(1)(byr-1,nyrRetro-1)) + sig2R;
     break;
   }
  /**
   * @brief Calculate prior pdf
   * @details Function to calculate prior pdf
   * @param pType the type of prior
   * @param theta the parameter
   * @param p1 the first prior parameter
   * @param p2 the second prior parameter
  **/
}

dvariable model_parameters::get_prior_pdf(const int &pType, const dvariable &_theta, const double &p1, const double &p2)
{
  {
   dvariable prior_pdf;
   switch(pType)
    {
      case UNIFORM_PRIOR: // uniform
       prior_pdf = dunif(_theta,p1,p2);
       break;
      case NORMAL_PRIOR: // normal
       prior_pdf = dnorm(_theta,p1,p2);
       break;
      case LOGNORMAL_PRIOR: // lognormal
       prior_pdf = dlnorm(_theta,log(p1),p2);
       break;
      case BETA_PRIOR: // beta
       prior_pdf = dbeta(_theta,p1,p2);
       break;
      case GAMMA_PRIOR: // gamma
       prior_pdf = dgamma(_theta,p1,p2);
       break;
    }
   return prior_pdf;
  }
  /**
   * @brief Calculate prior density functions for leading parameters.
   * @details
   *  - case 0 is a uniform density between the lower and upper bounds.
   *  - case 1 is a normal density with mean = p1 and sd = p2
   *  - case 2 is a lognormal density with mean = log(p1) and sd = p2
   *  - case 3 is a beta density bounded between lb-ub with p1 and p2 as alpha & beta
   *  - case 4 is a gamma density with parameters p1 and p2.
   *
   *  TODO
   *  Make this a generic function.
   *  Agrs would be vector of parameters, and matrix of controls
   *  @param theta a vector of parameters
   *  @param C matrix of controls (priorType, p1, p2, lb, ub)
   *  @return vector of prior densities for each parameter
  **/
}

void model_parameters::calc_prior_densities(void)
{
  double p1,p2;
  double lb,ub;
  int iprior,itype;
  dvariable x;
  // Initialize
  priorDensity.initialize();
  // Key parameter priors
  iprior = 1;
  for ( int i = 1; i <= ntheta; i++ )
   {
    if ( theta_phz(i) > 0 & theta_phz(i) <= current_phase() )
     {
      itype = int(theta_control(i,5));
      p1 = theta_control(i,6);
      p2 = theta_control(i,7);
      dvariable x = theta(i);
      if ( itype == 3 )
       { lb = theta_control(i,2); ub = theta_control(i,3); x = (x - lb) / (ub - lb); }
      priorDensity(iprior) = get_prior_pdf(itype, x, p1, p2);
      iprior += 1;
     }
   }
  // Growth parameter priors
  for ( int i = 1; i <= nGrwth; i++ )
   {
    if ( Grwth_phz(i) > 0 & Grwth_phz(i) <= current_phase() )
     {
      itype = int(Grwth_control(i,5));
      p1 = Grwth_control(i,6);
      p2 = Grwth_control(i,7);
      dvariable x = Grwth(i);
      if ( itype == 3 )
       { lb = Grwth_control(i,2); ub = Grwth_control(i,3); x = (x - lb) / (ub - lb); }
      priorDensity(iprior) = get_prior_pdf(itype, x, p1, p2);
      iprior += 1;
     }
   }
  // Selctivity parameter priors
  int j = 1;
  for ( int k = 1; k <= nslx; k++ )
   for ( int i = 1; i <= slx_cols(k); i++ )
    {
     if ( slx_phzm(j) > 0 & slx_phzm(j) <= current_phase() )
      {
       itype = int(slx_priors(k,i,1));
       p1 = slx_priors(k,i,2);
       p2 = slx_priors(k,i,3);
       if ( slx_type(k) == 0 || slx_type(k) == 1 )
        x = mfexp(log_slx_pars(j)) / (1 + mfexp(log_slx_pars(j)));
       else
        x = mfexp(log_slx_pars(j));
       // Above is a change of variable so an adjustment is required - DOUBLE CHECK THIS
       //priorDensity(iprior) = get_prior_pdf(itype, x, p1, p2) + log_slx_pars(k,j);
       priorDensity(iprior) = get_prior_pdf(itype, x, p1, p2);
       if ( verbose >= 2 ) cout << " Prior no, val, dens " << iprior << " " << x << " " << priorDensity(iprior) << endl;
       iprior++;
      }
     j++;
    }
  // Asymptotic selectivity
  for ( int i = 1; i <= NumAsympRet; i++ )
   {
    if ( AsympSel_phz(i) > 0 & AsympSel_phz(i) <= current_phase() )
     {
      itype = 0;
      p1 = AsympSel_lb(i);
      p2 = AsympSel_ub(i);
      dvariable x = Asymret(i);
      priorDensity(iprior) = get_prior_pdf(itype, x, p1, p2);
      iprior += 1;
     }
   }
  // No priors on fbar and foff
  for (int i=1; i<=nfleet; i++) if (f_phz(i) > 0 & f_phz(i) <= current_phase()) iprior += 1;
  for (int i=1; i<=nfleet; i++) if (f_phz(i) > 0 & f_phz(i) <= current_phase()) iprior += nFparams(i);
  for (int i=1; i<=nfleet; i++) if (foff_phz(i) > 0 & foff_phz(i) <= current_phase()) iprior += 1;
  for (int i=1; i<=nfleet; i++) if (foff_phz(i) > 0 & foff_phz(i) <= current_phase()) iprior += nYparams(i);
  // no priors on the recruitments (well apart from the later ones)
  if (rec_ini_phz > 0 & rdv_phz <= current_phase()) iprior += nclass;
  if (rdv_phz > 0 & rdv_phz <= current_phase()) iprior += (rdv_eyr-rdv_syr+1);
  if (rec_prop_phz > 0 & rec_prop_phz <= current_phase()) iprior += (rdv_eyr-rdv_syr+1);
  // Natural mortality
  for ( int i = 1; i <= nMdev; i++ )
   {
    if ( Mdev_phz(i) > 0 & Mdev_phz(i) <= current_phase() )
     {
      itype = 0;
      p1 = Mdev_lb(i);
      p2 = Mdev_ub(i);
      dvariable x = m_dev_est(i);
      priorDensity(iprior) = get_prior_pdf(itype, x, p1, p2);
      iprior += 1;
     }
   }
  // No priors for effectine sample sizes
  for (int i=1;i<=nSizeComps; i++) if (nvn_phz(i) > 0 & nvn_phz(i) <= current_phase()) iprior += 1;
  // Catchability parameter priors
  for ( int i = 1; i <= nSurveys; i++ )
   if (q_phz(i) > 0 & q_phz(i) <= current_phase() )
    {
     priorDensity(iprior) = get_prior_pdf(prior_qtype(i), survey_q(i), prior_p1(i), prior_p2(i));
     if ( last_phase() )
      priorDensity(iprior) = priorDensity(iprior) ;
     else
      priorDensity(iprior) = 0.1 * priorDensity(iprior) ;
     iprior++;
    }
  // Additional CV parameter priors
  for ( int i = 1; i <= nSurveys; i++ )
   {
    if ( cv_phz(i) > 0 & cv_phz(i) <= current_phase() )
     {
      itype = int(prior_add_cv_type(i));
      if (itype == 0)
       {
        p1 = add_cv_lb(i);
        p2 = add_cv_ub(i);
       }
      else
       {
        p1 = prior_add_cv_p1(i);
        p2 = prior_add_cv_p2(i);
       }
      priorDensity(iprior) = get_prior_pdf(itype, mfexp(log_add_cv(i)), p1, p2);
      iprior += 1;
     }
   }
     // IMmature/mature natural mortality parameter priors
  for ( int i = 1; i <= nsex; i++ )
   {
    if ( m_mat_phz(i) > 0 & m_mat_phz(i) <= current_phase() )
     {
      itype = int(prior_m_mat_type(i));
      if (itype == 0)
       {
        p1 = m_mat_lb(i);
        p2 = m_mat_ub(i);
       }
      else
       {
        p1 = (prior_m_mat_p1(i));
        p2 = prior_m_mat_p2(i);
       }
      priorDensity(iprior) = get_prior_pdf(itype, (m_mat_mult(i)), p1, p2);
      iprior += 1;
     }
   }
}

void model_parameters::catch_likelihood(void)
{
 dvariable effort;
  // 1) Likelihood of the catch data.
  res_catch.initialize();
  for ( int k = 1; k <= nCatchDF; k++ )
   {
    for ( int jj = 1; jj <= nCatchRows(k); jj++ )
     if (dCatchData(k,jj,1) <= nyrRetro)
      {
       effort =   dCatchData(k,jj,10);                                ///> Effort data
       // In first case (obs_catch > 0) then if there is only catch data, calculate the residual as per usual; if there is catch and effort data, then still use observed catch to calculate the residual, despite the predicted catch being calculated differently.
       // In second case, when effort > 0 then the residual is the pred catch using Fs - pred catch using q
       if ( obs_catch(k,jj) > 0.0 )
        {
         res_catch(k,jj) = log(obs_catch(k,jj)) - log(pre_catch(k,jj));
        }
       else
        if (effort > 0.0)
         {
          res_catch(k,jj) = log(obs_catch_effort(k,jj)) - log(pre_catch(k,jj));
         }
      }
     dvector catch_sd = sqrt(log(1.0 + square(catch_cv(k))));
     nloglike(1,k) += dnorm(res_catch(k), catch_sd);
   }
  if ( verbose >= 3 ) cout << "Ok after catch likelihood ..." << endl;
}

void model_parameters::index_likelihood(void)
{
  // 2) Likelihood of the relative abundance data.
  for ( int k = 1; k <= nSurveys; k++ )
   {
    for ( int jj = 1; jj <= nSurveyRows; jj++ )
     if (dSurveyData(jj,0) == k)
      {
       if ( active(log_add_cv(k)) )                                                              ///> Estimated additional variance
        {
         dvariable stdtmp = sqrt(log(1.0 + square(cpue_cv(jj)) + square(mfexp(log_add_cv(k)))));
         nloglike(2,k) += log(stdtmp) + 0.5 * square(res_cpue(jj) / stdtmp);
        }
      else
       {
        dvariable stdtmp = cpue_sd(jj) * 1.0 / cpue_lambda(k);                                  ///> Use Sigma scalar instead
        nloglike(2,k) += log(stdtmp) + 0.5 * square(res_cpue(jj) / stdtmp);
       }
     }  
   }
  if ( verbose >= 3 ) cout << "Ok after survey index likelihood ..." << endl;
}

void model_parameters::length_likelihood(void)
{
  // 3) Likelihood for size composition data.
  d3_res_size_comps.initialize();
  for ( int ii = 1; ii <= nSizeComps; ii++ )
   {
    dmatrix O = d3_obs_size_comps(ii);                                                        ///> Observed length frequency
    dvar_matrix P = d3_pre_size_comps(ii);                                                    ///> Predicted length-frequency
    dvar_vector log_effn = log(mfexp(log_vn(ii)) * size_comp_sample_size(ii) * lf_lambda(ii));///> Effective sample size
    bool bCmp = bTailCompression(ii);
    class acl::negativeLogLikelihood *ploglike;                                               ///> Negative log-likelihood
    switch ( nAgeCompType(ii) )                                                               ///> Select option for size-comp data
     {
      case 0:                                                                                 ///> ignore composition data in model fitting.
       ploglike = NULL;
       break;
      case 1:                                                                                 ///> multinomial with fixed or estimated n
       ploglike = new class acl::multinomial(O, bCmp);
       break;
      case 2:                                                                                 ///> robust approximation to the multinomial
       ploglike = new class acl::robust_multi(O, bCmp);
       break;
      case 5:                                                                                 ///> Dirichlet
       ploglike = new class acl::dirichlet(O, bCmp);
       break;
     }
    if ( ploglike != NULL )                                                                   ///> extract the residuals
     d3_res_size_comps(ii) = ploglike->residual(log_effn, P);
    if ( ploglike != NULL )                                                                   ///> Compute the likelihood
     {
      nloglike(3,ii) += ploglike->nloglike(log_effn, P);
      delete ploglike;
     }
   }
  if ( verbose >= 3 ) cout << "Ok after composition likelihood ..." << endl;
}

void model_parameters::recruitment_likelihood(void)
{
  // 4) Likelihood for recruitment deviations.
  dvariable sigR = mfexp(logSigmaR);
  nloglike(4,1) = dnorm(res_recruit, sigR);                          ///> Post first year devs
  if (active(rec_ini)) nloglike(4,2) += dnorm(rec_ini, sigR);                             ///> Initial devs (not used?)
  switch ( nSRR_flag )
    {
     case 0:                                                         ///> Constant recruitment
      break;
     case 1:
        //nloglike(4,1) = dnorm(res_recruit, sigR);                  ///> Stock-recruitment relationship (not used)
      break;
    }
  if ( active(logit_rec_prop_est) )                                  ///> Sex-ratio devs
   nloglike(4,3) += dnorm(logit_rec_prop_est, 2.0);
  if ( verbose >= 3 ) cout << "Ok after recruitment likelihood ..." << endl;
  // 5) Likelihood for growth increment data #1
  if (bUseGrowthIncrementModel==LINEAR_GROWTHMODEL & GrowthObsType==GROWTHINC_DATA)
    {
    dvar_vector MoltIncPred = calc_growth_increments(dPreMoltSize, iMoltIncSex);
    nloglike(5,1) = dnorm(log(dMoltInc) - log(MoltIncPred), dMoltIncCV);
   }
  if ( verbose >= 3 ) cout << "Ok after increment likelihood 1 ..." << endl;
}

void model_parameters::growth_likelihood(void)
{
  dvariable Prob;
  //  5) Likelihood for the size-class change data #2
  if (GrowthObsType==GROWTHCLASS_DATA)
   {
    // First find all FullY matrices
    FullY.initialize();
    for (int h = 1; h <=nsex; h++)
     for (int k = 1; k<=nSizeIncVaries(h);k++)
      {
       FullY(h,k,1) = growth_transition(h,k);
       for (int itime=2;itime<=MaxGrowTimeLibSex(h);itime++) FullY(h,k,itime) = FullY(h,k,itime-1)*growth_transition(h,k);
      }
    for (int i=1;i<=nGrowthObs;i++)
     {
      int h = iMoltIncSex(i);
      int k = iMoltTrans(i);
      int iclassRel = iMoltInitSizeClass(i);
      int iclassRec = iMoltEndSizeClass(i);
      int itimeLib = iMoltTimeAtLib(i);
      int ifleetRec = iMoltFleetRecap(i);
      int iyearRec = iMoltYearRecap(i);
      double freq = float(iMoltSampSize(i));
      Prob = FullY(h,k,itimeLib,iclassRel,iclassRec)*exp(log_slx_capture(ifleetRec,h,iyearRec,iclassRec))+1.0e-20;
      dvariable total = 0;
      for (int i=1;i<=nSizeSex(h);i++) total += FullY(h,k,itimeLib,iclassRel,i)*exp(log_slx_capture(ifleetRec,h,iyearRec,i));
      nloglike(5,h) += log(Prob/total)*freq;
     }
   } // Growth data
  if ( verbose >= 3 ) cout << "Ok after increment likelihood 2 ..." << endl;
  /**
   * @brief calculate objective function
   * @details
   *
   * Likelihood components
   *  -# likelihood of the catch data (assume lognormal error)
   *  -# likelihood of relative abundance data
   *  -# likelihood of size composition data
   *
   * Penalty components
   *  -# Penalty on log_fdev to ensure they sum to zero.
   *  -# Penalty to regularize values of log_fbar.
   *  -# Penalty to constrain random walk in natural mortaliy rates
  **/
}

void model_parameters::calc_objective_function(void)
{
  // |---------------------------------------------------------------------------------|
  // | NEGATIVE LOGLIKELIHOOD COMPONENTS FOR THE OBJECTIVE FUNCTION                    |
  // |---------------------------------------------------------------------------------|
  dvariable w_nloglike;
  dvariable SumRecF, SumRecM;
  // Reset the likelihood
  nloglike.initialize();
  catch_likelihood();
  index_likelihood();
  length_likelihood();
  recruitment_likelihood();
  growth_likelihood();
  // |---------------------------------------------------------------------------------|
  // | PENALTIES AND CONSTRAINTS                                                       |
  // |---------------------------------------------------------------------------------|
  nlogPenalty.initialize();
  // 1) Penalty on log_fdev (male+combined; female) to ensure they sum to zero
  for ( int k = 1; k <= nfleet; k++ )
   {
    dvariable s     = mean(log_fdev(k));
    nlogPenalty(1) += s*s;
    if (nsex > 0)
     {
      dvariable r     = mean(log_fdov(k));
      nlogPenalty(1) += r*r;
     }
   }
  // 2) Penalty on mean F to regularize the solution.
  int irow = 1;
  if ( last_phase() ) irow = 2;
  dvariable fbar;
  dvariable ln_fbar;
  for ( int k = 1; k <= nfleet; k++ )
   {
    // Jim made penalty apply only to season 2 for Fbar ft(1,nfleet,1,nsex,syr,nyrRetro,1,nseason);            ///> Fishing mortality by gear
    fbar = mean( trans(ft(k,1))(2) );
    if ( pen_fbar(k) > 0 && fbar != 0 )
     {
      ln_fbar = log(fbar);
      nlogPenalty(2) += dnorm(ln_fbar, log(pen_fbar(k)), pen_fstd(irow,k));
     }
   }
  // 3) Penalty to constrain M in random walk
  if (nMdev > 0)
   nlogPenalty(3) += dnorm(m_dev_est, m_stdev);
  // 5-6) Penalties on recruitment devs.
  if ( !last_phase() )
   {
    if ( active(rec_ini) && nSRR_flag !=0 ) nlogPenalty(5) = dnorm(rec_ini, 1.0);
    if ( active(rec_dev_est) ) nlogPenalty(6) = dnorm(first_difference(rec_dev), 1.0);
   }
  // 7) Penalties on sex-specific recruitment
  if (nsex > 1)
   {
    SumRecF = 0; SumRecM = 0;
    for ( int i = syr; i <= nyrRetro; i++ )
     { SumRecF += recruits(2)(i); SumRecM += recruits(1)(i); }
    nlogPenalty(7) = square(log(SumRecF) - log(SumRecM));
   }
   // 8) Smoothness penalty on molting probability
   if (bUseCustomMoltProbility==FREE_PROB_MOLT)
   {
     for (int igrow=1;igrow<=nMoltVaries(1);igrow++)
	 {	 
	  nlogPenalty(8) += dnorm(first_difference(molt_probability_in(1,igrow)), 1.0);  
	  nlogPenalty(8) += dnorm(first_difference(molt_probability_in(2,igrow)), 1.0);  
     }
   }
   // 9) Smoothness penalty on free selectivity
  for ( int k = 1; k <= nslx; k++ )
   if( slx_type(k) == SELEX_PARAMETRIC)
   {
	int kk = abs(slx_gear(k));  
	for(int h =1; h<=nsex;h++)
	  nlogPenalty(9) += dnorm(first_difference(log_slx_capture(kk,h,syr)), 1.0); 
   }
  w_nloglike = sum(elem_prod(nloglike(1),catch_emphasis)) + sum(elem_prod(nloglike(2),cpue_emphasis)) + sum(elem_prod(nloglike(3),lf_emphasis));
  w_nloglike += sum(nloglike(4));
  w_nloglike += sum(nloglike(5));
  objfun =  w_nloglike + sum(elem_prod(nlogPenalty,Penalty_emphasis))+ sum(priorDensity) + TempSS;
  // Summary tables
  if ( verbose >= 2 ) cout << "Penalties: " << nlogPenalty << endl;
  if ( verbose >= 2 ) cout << "Penalties: " << elem_prod(nlogPenalty,Penalty_emphasis) << endl;
  if ( verbose >= 2 ) cout << "Likelihoods: " << endl;
  if ( verbose >= 2 ) cout << nloglike << endl;
  if ( verbose >= 1 ) cout  << "fn Call: " << current_phase() << " " << NfunCall << " " << objfun << " " << w_nloglike << " " << sum(elem_prod(nlogPenalty,Penalty_emphasis)) << " " << sum(priorDensity)+TempSS << endl;
  /**
   * @brief Simulation model
   * @details Uses many of the same routines as the assessment model, over-writes the observed data in memory with simulated data.
  **/
}

void model_parameters::simulation_model(void)
{
  // random number generator
  random_number_generator rng(rseed);
  // Initialize model parameters
  initialize_model_parameters();
  // Fishing fleet dynamics ...
  calc_selectivities();
  calc_fishing_mortality();
  dvector drec_dev(syr+1,nyrRetro);
  drec_dev.fill_randn(rng);
  rec_dev = mfexp(logSigmaR) * drec_dev;
  // Population dynamics ...
  calc_growth_increments();
  calc_molting_probability();
  calc_growth_transition();
  calc_natural_mortality();
  calc_total_mortality();
  calc_recruitment_size_distribution();
  calc_initial_numbers_at_length();
  update_population_numbers_at_length();
  // observation models ...
  calc_predicted_catch();
  calc_relative_abundance();
  calc_predicted_composition();
  // add observation errors to catch.
  dmatrix err_catch(1,nCatchDF,1,nCatchRows);
  err_catch.fill_randn(rng);
  dmatrix catch_sd(1,nCatchDF,1,nCatchRows);
  for ( int k = 1; k <= nCatchDF; k++ )
   {
    catch_sd(k)  = sqrt(log(1.0 + square(catch_cv(k))));
    obs_catch(k) = value(pre_catch(k));
    err_catch(k) = elem_prod(catch_sd(k), err_catch(k)) - 0.5*square(catch_sd(k));
    obs_catch(k) = elem_prod(obs_catch(k), mfexp(err_catch(k)));
    for ( int i = syr; i <= nyrRetro; i++ )
     for ( int ii = 1; ii <= nCatchRows(k); ii++ )
      {
       if ( dCatchData(k,ii,1) == dCatchData_out(k,i,1) ) // year index
        {
         obs_catch_out(k,i) = obs_catch(k,ii);
         dCatchData_out(k,i,5) = obs_catch(k,ii);
        }
       }
   }
  // add observation errors to cpue & fill in dSurveyData column 5
  dvector err_cpue(1,nSurveyRows);
  dvector cpue_sd_sim = sqrt(log(1.0 + square(cpue_cv))); // Note if this should include add_cv
  err_cpue.fill_randn(rng);
  obs_cpue = value(pre_cpue);
  err_cpue = elem_prod(cpue_sd_sim,err_cpue) - 0.5*square(cpue_sd_sim);
  obs_cpue = elem_prod(obs_cpue,mfexp(err_cpue));
  for ( int k = 1; k <= nSurveyRows; k++ )
   dSurveyData(k,6) = obs_cpue(k);
  // add sampling errors to size-composition.
  double tau;
  for ( int k = 1; k <= nSizeComps; k++ )
   for ( int i = 1; i <= nSizeCompRows(k); i++ )
    {
     tau = sqrt(1.0 / size_comp_sample_size(k)(i));
     dvector p = value(d3_pre_size_comps(k)(i));
     d3_obs_size_comps(k)(i) = rmvlogistic(p,tau,rseed+k+i);
    }
  /**
   * @brief Calculate mature male biomass (MMB)
   * @details Calculation of the mature male biomass is based on the numbers-at-length summed over each shell condition.
   *
   * TODO: Add female component if lamda < 1
   *
   * @return dvar_vector ssb (model mature biomass).
  **/
}

dvar_vector model_parameters::calc_ssb()
{
  int ig,h,m,o;
  dvar_vector ssb(syr,nyrRetro);
  ssb.initialize();
  for ( int i = syr; i <= nyrRetro; i++ )
   for ( ig = 1; ig <= n_grp; ig++ )
    {
     h = isex(ig);
     o = ishell(ig);
     m = imature(ig);
     double lam;
     h <= 1 ? lam = spr_lambda : lam = (1.0 - spr_lambda);
	 if(nmature==1)
      ssb(i) += lam * d4_N(ig)(i)(season_ssb) * elem_prod(mean_wt(h)(i), maturity(h));
  	 if(nmature==2)
	  if(m==1)
       ssb(i) += lam * d4_N(ig)(i)(season_ssb) * mean_wt(h)(i);
    }
  return(ssb);
  // Andre
  /**
   * @brief Calculate equilibrium initial conditions
   *
   * @return dvar_matrix
  **/
}

dvar_matrix model_parameters::calc_brute_equilibrium(const int YrRefSexR1, const int YrRefSexR2, const int YrRef, const int ninit)
{
  int isizeTrans;
  double xi;                                                               ///> discard mortality rate
  dvariable log_ftmp;
  dvariable ssb_use;
  dvariable TotalRec;
  dvariable TotalSex1,TotalAll,SexRatio;                                   ///> used to compute the sex ratio for future recruitment
  dvar_matrix rtt(1,nsex,1,nclass);                                        ///> constant recruitment
  dvar4_array d4_N_init(1,n_grp,1,ninit,1,nseason,1,nclass);               ///> N matrix
  dvar3_array d4_Npass(1,n_grp,1,nseason,1,nclass);                        ///> Use to compute reference points
  dvar_matrix equilibrium_numbers(1,n_grp,1,nclass);                       ///> Final numbers-at-size
  dvar_vector x(1,nclass);                                                 ///> Temp vector for numbers
  dvar_vector y(1,nclass);                                                 ///> Temp vector for numbers
  dvar_vector z(1,nclass);                                                 ///> Temp vector for numbers
  dvar_matrix MoltProb(1,nsex,1,nclass);                                   ///> Molting probability
  dvar3_array _ft(1,nfleet,1,nsex,1,nseason);                              ///> Fishing mortality by gear (fleet)
  dvar3_array FF1(1,nsex,1,nseason,1,nclass);                              ///> Fishing mortality (continuous)
  dvar3_array FF2(1,nsex,1,nseason,1,nclass);                              ///> Fishing mortality (instantaneous)
  dvar4_array ZZ1(1,nsex,1,nmature,1,nseason,1,nclass);                              ///> Total mortality (continuous)
  dvar4_array ZZ2(1,nsex,1,nmature,1,nseason,1,nclass);                              ///> Total mortality (instananeous)
  dvar5_array SS(1,nsex,1,nmature,1,nseason,1,nclass,1,nclass);                      ///> Surival Rate
  dvar_vector ssb_prj(syr,nyr+ninit);                                      ///> projected spawning biomass
  dvar_vector hist_ssb(syr,nyr);                                           ///> Historical SSB
  dvar_vector Rec_use(1,nsex);                                             ///> Recruitment
  dvar_vector sel(1,nclass);                                               ///> Capture selectivity
  dvar_vector selret(1,nclass);                                            ///> Selectvity x retained
  dvar_vector ret(1,nclass);                                               ///> Retained probability
  dvar_vector vul(1,nclass);                                               ///> Total vulnerability
  dvar_vector nal(1,nclass);                                               ///> Numbers-at-length
  dvar_vector tempZ1(1,nclass);                                            ///> Total mortality
  dvar_vector out(1,2+nfleet);
  // Initialize
  d4_N_init.initialize();
  // copy SSB into projection SSB
  hist_ssb = calc_ssb();
  ssb_prj.initialize();
  for (int i = syr; i<=nyrRetro;i++) ssb_prj(i) = hist_ssb(i);
  // set the molt probability (depends on first vs last year)
  for (int h = 1; h <= nsex; h++ )
   for (int l=1;l<=nclass;l++)
    MoltProb(h,l) = molt_probability(h,YrRef,l);
  // Initialize the Fs
  FF1.initialize();
  for ( int h = 1; h <= nsex; h++ )
   for ( int j = 1; j <= nseason; j++ )
    for ( int l = 1; l <= nclass; l++)
     FF2(h,j,l) = 1.0e-10;
  // compute the F matrix
  for ( int k = 1; k <= nfleet; k++ )
   for ( int h = 1; h <= nsex; h++ )
    for ( int j = 1; j <= nseason; j++ )
     if ( fhit(YrRef,j,k) )
      {
       log_ftmp = log_fimpbar(k);
       if (h==2) log_ftmp += log_foff(k);
       _ft(k,h,j) = mfexp(log_ftmp);
       xi  = dmr(YrRef,k);                                                       // Discard mortality rate
       sel = mfexp(log_slx_capture(k,h,YrRef))+1.0e-10;                          // Selectivity
       ret = mfexp(log_slx_retaind(k,h,YrRef)) * slx_nret(h,k);                  // Retension
       vul = elem_prod(sel, ret + (1.0 - ret) * xi);                             // Vulnerability
       FF1(h,j) += _ft(k,h,j) * vul;
       FF2(h,j) += _ft(k,h,j) * sel;
      }
  // computer the total mortality
  ZZ1.initialize(); ZZ2.initialize(); SS.initialize();
  for(int m = 1; m <=nmature;m++)
  for ( int h = 1; h <= nsex; h++ )
   for ( int j = 1; j <= nseason; j++ )
    {
     ZZ1(h,m,j) = (m_prop(YrRef,j) * M(h,m,YrRef)) + FF1(h,j);
     ZZ2(h,m,j) = (m_prop(YrRef,j) * M(h,m,YrRef)) + FF2(h,j);
     if (season_type(j) == 0) for ( int l = 1; l <= nclass; l++ ) SS(h,m,j)(l,l) = 1.0-ZZ1(h,m,j,l)/ZZ2(h,m,j,l)*(1.0-mfexp(-ZZ2(h,m,j,l)));
     if (season_type(j) == 1) for ( int l = 1; l <= nclass; l++ ) SS(h,m,j)(l,l) = mfexp(-ZZ1(h,m,j,l));
    }
  // recruitment distribution
  if (nsex>1)
   {
    TotalSex1 = 0; TotalAll = 0;
    for (int i=YrRefSexR1;i<=YrRefSexR2;i++) 
     {
      TotalSex1 += 1 / (1 + mfexp(-logit_rec_prop(i)));
      TotalAll += 1;
     }
    SexRatio = TotalSex1/TotalAll;
    spr_sexr = SexRatio;
    // AEP reset
    switch( bSteadyState )
     {
      case UNFISHEDEQN: // Unfished conditions
       rtt(1) = mfexp(logR0) * SexRatio * rec_sdd(1);
       rtt(2) = mfexp(logR0) * (1 - SexRatio) * rec_sdd(2);
       break;
      case FISHEDEQN: // Steady-state fished conditions
       rtt(1) = mfexp(logRini) * SexRatio * rec_sdd(1);
       rtt(2) = mfexp(logRini) * (1 - SexRatio) * rec_sdd(2);
       break;
      case FREEPARS: // Free parameters
       rtt(1) = mfexp(logRbar) * SexRatio * rec_sdd(1);
       rtt(2) = mfexp(logRbar) * (1 - SexRatio) * rec_sdd(2);
       break;
      case FREEPARSSCALED: // Free parameters (revised)
       rtt(1) = mfexp(logRbar) * SexRatio * rec_sdd(1);
       rtt(2) = mfexp(logRbar) * (1 - SexRatio) * rec_sdd(2);
       break;
      case REFPOINTS: // Reference points
       rtt(1) = spr_rbar * SexRatio * rec_sdd(1);
       rtt(2) = spr_rbar * (1 - SexRatio) * rec_sdd(2);
       break;
     }
   }
  else
   {
    spr_sexr = 1;
    switch( bSteadyState )
     {
      case UNFISHEDEQN: // Unfished conditions
       rtt(1) = mfexp(logR0) * rec_sdd(1);
       break;
      case FISHEDEQN: // Steady-state fished conditions
       rtt(1) = mfexp(logRini) * rec_sdd(1);
       break;
      case FREEPARS: // Free parameters
       rtt(1) = mfexp(logRbar) * rec_sdd(1);
       break;
      case FREEPARSSCALED: // Free parameters (revised)
       rtt(1) = mfexp(logRbar) * rec_sdd(1);
       break;
      case REFPOINTS: // Reference points
       rtt(1) = spr_rbar * rec_sdd(1);
       break;
     }
   }
  // Now project to find the equilibrium
  for ( int i = 1; i < ninit; i++ )
   {
    // Recruitment
    if (Eqn_basis != CONSTANTREC)
     {
      if (Stock_rec_prj==RICKER)
       {
        ssb_use = ssb_prj(nyrRetro+i-Age_at_rec_prj);
        TotalRec = SR_alpha_prj*ssb_use*exp(-1*SR_beta_prj*ssb_use);
        if (nsex>1)
         {
          rtt(1) = TotalRec * 1 / (1 + mfexp(-logit_rec_prop(YrRef))) * rec_sdd(1);
          rtt(2) = TotalRec * (1 - 1 / (1 + mfexp(-logit_rec_prop(YrRef)))) * rec_sdd(2);
         }
        else
         rtt(1) = TotalRec * rec_sdd(1);
       }
      if (Stock_rec_prj==BEVHOLT)
       {
        ssb_use = ssb_prj(nyrRetro+i-Age_at_rec_prj);
        TotalRec = SR_alpha_prj*ssb_use/(SR_beta_prj+ssb_use);
        if (nsex>1)
         {
          rtt(1) = TotalRec * 1 / (1 + mfexp(-logit_rec_prop(YrRef))) * rec_sdd(1);
          rtt(2) = TotalRec * (1 - 1 / (1 + mfexp(-logit_rec_prop(YrRef)))) * rec_sdd(2);
         }
        else
         rtt(1) = TotalRec * rec_sdd(1);
       }
     }
    for ( int j = 1; j <= nseason; j++ )
     for ( int ig = 1; ig <= n_grp; ig++ )
      {
       int h = isex(ig);
       isizeTrans = iYrIncChanges(h,YrRef);
       int m = imature(ig);
       int o = ishell(ig);
       x = d4_N_init(ig,i,j);
       // Mortality (natural and fishing)
       x = x * SS(h,m,j);
       if ( nshell == 1 )
        {
	    if(nmature == 1)
		 {
         // Molting and growth
         if (j == season_growth)
          {
           y = elem_prod(x, 1 - MoltProb(h)); // did not molt, becomes oldshell
           x = elem_prod(x, MoltProb(h)) * growth_transition(h,isizeTrans); // molted and grew, stay newshell
           x += y;
          }
         // Recruitment
         if (j == season_recruitment) x += rtt(h);
         if (j == nseason)
          d4_N_init(ig)(i+1)(1) = x;
         else
          d4_N_init(ig)(i)(j+1) = x;
	  }
        if(nmature == 2)
		 {
		  if ( m == 1 ) // mature
          {
           //No molting, growth, or recruitment for mature animals
           if (j == nseason) d4_N_init(ig)(i+1)(1) = x; else  d4_N_init(ig)(i)(j+1) = x;
          }
          if ( m == 2 ) // immature
          {
          // Molting and growth
           z.initialize();
           if (j == season_growth)
            {
             //z = elem_prod(x, molt_probability(h)(i)) * growth_transition(h,isizeTrans); 		// molted to maturity
             //x = elem_prod(x, 1 - molt_probability(h)(i)) * growth_transition(h,isizeTrans);    // molted, but immature
			 z = elem_prod(x * growth_transition(h,isizeTrans), MoltProb(h)) ; 		// molted to maturity
             x = elem_prod(x * growth_transition(h,isizeTrans), 1 - MoltProb(h)) ;    // molted, but immature
            }
		   if (j == season_recruitment) x += rtt(h);
           if (j == nseason)
            { d4_N_init(ig-1)(i+1)(1) += z; d4_N_init(ig)(i+1)(1) = x; }
            else
            { d4_N_init(ig-1)(i)(j+1) += z; d4_N_init(ig)(i)(j+1) = x; }
          }	 
		 }
        }
       else
        {
         if ( o == 1 ) // newshell
          {
           // Molting and growth
           if (j == season_growth)
            {
             y = elem_prod(x, 1 - MoltProb(h)); // did not molt, becomes oldshell
             x = elem_prod(x, MoltProb(h)) * growth_transition(h,isizeTrans); // molted and grew, stay newshell
            }
           // Recruitment
           if (j == season_recruitment)  x += rtt(h);
           if (j == nseason)
            d4_N_init(ig)(i+1)(1) = x;
           else
            d4_N_init(ig)(i)(j+1) = x;
          }
         if ( o == 2 ) // oldshell
          {
           // Molting and growth
           z.initialize();
           if (j == season_growth)
            {
             z = elem_prod(x, MoltProb(h)) * growth_transition(h,isizeTrans); // molted and grew, become newshell
             x = elem_prod(x, 1 - MoltProb(h)) + y; // did not molt, remain oldshell and add the newshell that become oldshell
            }
           if (j == nseason)
            { d4_N_init(ig-1)(i+1)(1) += z; d4_N_init(ig)(i+1)(1) = x; }
           else
            { d4_N_init(ig-1)(i)(j+1) += z; d4_N_init(ig)(i)(j+1) = x; }
          }
        }
      } // j
     // Project SSB
     for ( int ig = 1; ig <= n_grp; ig++ )
      {
       int h = isex(ig);
       int o = ishell(ig);
       int m = imature(ig);
       double lam;
       h <= 1 ? lam = spr_lambda: lam = (1.0 - spr_lambda);
	   if(nmature ==1)
        ssb_prj(nyrRetro+i) += lam * d4_N_init(ig)(i)(season_ssb) * elem_prod(mean_wt(h,YrRef), maturity(h));
	   if(nmature ==2)
		if(m==1)
		{
         ssb_prj(nyrRetro+i) += lam * d4_N_init(ig)(i)(season_ssb) * mean_wt(h,YrRef);
		 //cout<<"d4_N_init(ig)(i)(season_ssb)"<<d4_N_init(ig)(i)(season_ssb)<<endl;
		 //cout<<"mean_wt(h,YrRef)"<<mean_wt(h,YrRef)<<endl;
		 //cout<<"lam"<<lam<<endl;
		 //cout<<"output"<<ssb_prj(nyrRetro+i)<<endl;
		}
      }
   } // i
  // Extract the equilibrium numbers (for return)
  for ( int ig = 1; ig <= n_grp; ig++ )
   equilibrium_numbers(ig) = d4_N_init(ig)(ninit)(1);
  // ssb to reurn
  ssb_pass = ssb_prj(nyrRetro+ninit-1);
  // Projected catche
  for ( int j = 1; j <= nseason; j++ )
   for ( int ig = 1; ig <= n_grp; ig++ )
    d4_Npass(ig,j) = d4_N_init(ig)(ninit-1)(j);
  out = calc_predicted_project(nyrRetro, d4_Npass, _ft, ZZ1, ZZ2);
  oflret_pass = out(1); ofltot_pass = out(2);
  return(equilibrium_numbers);
}

dvar_vector model_parameters::project_biomass(const int YrRef, const int iproj)
{
  double lam,TACType;
  int isizeTrans;
  dvariable NF,MMARef,MLARef,StateTAC,TAC2,TargetC;                       ///> Various temps
  dvariable ssb_use,TotalRec,Fmin,Fmax,Fmult;                             ///> More temps
  dvar_vector FederalStuff(1,3);                                          ///> OFLs, ABCs etc
  dvar_matrix rtt(1,nsex,1,nclass);                                       ///> Constant recuitment
  dvar_vector MMAState(syr,nyr+iproj);                                    ///> Mature male ABUNDANCE (used in the control rule)
  dvar_vector MLAState(syr,nyr+iproj);                                    ///> Legal male ABUNDANCE (used in the control rule)
  dvar_vector ssb_prj(syr,nyr+iproj);                                     ///> projected spawning biomass
  dvar_vector hist_ssb(syr,nyr);                                          ///> Historical SSB
  dvar_vector Rec_use(1,nsex);                                            ///> Recruitment
  dvar4_array numbers_proj_gytl(1,n_grp,1,iproj,1,nseason,1,nclass);      ///> The N matrix for the projection
  dvar4_array d4_PassBack(1,n_grp,1,2,1,nseason,1,nclass);                ///> matrix to be returned
  dvar_matrix d4_Pass(1,n_grp,1,nclass);                                  ///> Numbers-at-sex/mature/shell/length.
  dvar_matrix MoltProb(1,nsex,1,nclass);                                  ///> Molt probability
  // Copy N from the end of the assessment into the first projection year
  numbers_proj_gytl.initialize();
  for ( int ig = 1; ig <= n_grp; ig++ ) numbers_proj_gytl(ig)(1)(1) = d4_N(ig)(nyrRetro+1)(1);
  // copy SSB into projection SSB
  hist_ssb = calc_ssb();
  ssb_prj.initialize();
  for (int i = syr; i<=nyrRetro;i++) ssb_prj(i) = hist_ssb(i);
  // set the molt probability (depends on first vs last year)
  for (int h = 1; h <= nsex; h++ )
   for (int l=1;l<=nclass;l++)
    MoltProb(h,l) = molt_probability(h,YrRef,l);
  // recruitment distribution (constant recruitment)
  if (nsex>1)
   {
    rtt(1) = spr_rbar / 2.0 * rec_sdd(1);
    rtt(2) = spr_rbar / 2.0 * rec_sdd(2);
   }
  else
   rtt(1) = spr_rbar * rec_sdd(1);
  // Compute MMA and MMB at the start of the season (needed for the State HCRs)
  MMAState.initialize();   MLAState.initialize();
  for ( int i = syr; i <= nyrRetro; i++ )
   {
    for ( int ig = 1; ig <= n_grp; ig++ )
     {
      int h = isex(ig);
      isizeTrans = iYrIncChanges(h,YrRef);
      int m = imature(ig);
      int o = ishell(ig);
      h <= 1 ? lam = spr_lambda: lam = (1.0 - spr_lambda);
	  if(nmature==1)
       MMAState(i) += sum(lam * elem_prod(d4_N(ig,i,1), maturity(h)));
   	  if(nmature==2)
	   if(m==1)	  
        MMAState(i) += sum(lam * d4_N(ig,i,1));
      MLAState(i) += sum(lam * elem_prod(d4_N(ig,i,1), legal(h)));
     }
   }
  MMARef = 0; MLARef = 0; NF = 0;
  for ( int i = 1978; i <= 2012; i++ ) { MMARef += MMAState(i); MLARef += MLAState(i); NF += 1; }
  MMARef /= NF; MLARef /= NF;
  // Now project forward
  for ( int i = 1; i <= iproj; i++ )
   {
    if (Stock_rec_prj==1)                           // Constant recruitment
     {
      for (int h=1; h<=nsex;h++) Rec_use(h) = fut_recruits(h,i);
     }
    if (Stock_rec_prj==RICKER)                      // Ricker
     {
      ssb_use = ssb_prj(nyrRetro+i-Age_at_rec_prj);
      TotalRec = SR_alpha_prj*ssb_use*exp(-1*SR_beta_prj*ssb_use)*fut_recruits(1,i);
      if (nsex>1)
       {
        Rec_use(1) = TotalRec * 1 / (1 + mfexp(-logit_rec_prop(YrRef)));
        Rec_use(2) = TotalRec * (1 - 1 / (1 + mfexp(-logit_rec_prop(YrRef))));
       }
      else
       Rec_use(1) = TotalRec;
     }
    if (Stock_rec_prj==BEVHOLT)                      // Beveton-Holt
     {
      ssb_use = ssb_prj(nyr+i-Age_at_rec_prj);
      TotalRec = SR_alpha_prj*ssb_use/(SR_beta_prj+ssb_use)*fut_recruits(1,i);
      if (nsex>1)
       {
        Rec_use(1) = TotalRec * 1 / (1 + mfexp(-logit_rec_prop(YrRef)));
        Rec_use(2) = TotalRec * (1 - 1 / (1 + mfexp(-logit_rec_prop(YrRef))));
       }
      else
       Rec_use(1) = TotalRec;
     }
    if (Stock_rec_prj==MEAN_RECRUIT)                    // Mean recruitment
     {
      TotalRec = mean_rec_prj;
      if (nsex>1)
       {
        Rec_use(1) = TotalRec * 1 / (1 + mfexp(-logit_rec_prop(YrRef)));
        Rec_use(2) = TotalRec * (1 - 1 / (1 + mfexp(-logit_rec_prop(YrRef))));
       }
      else
       Rec_use(1) = TotalRec;
     }
    // Store start-year N-at-size
    d4_Pass.initialize();
    for ( int ig = 1; ig <= n_grp; ig++ )  d4_Pass(ig) = numbers_proj_gytl(ig,i,1);
    // Compute the ABC and OFL
    FederalStuff = compute_OFL_and_ABC(nyr+i, d4_Pass);
    //cout << "Feds " << nyr+i << " " << FederalStuff << endl;
    // Compute MMA and MLA at the start of the season (needed for the State HCRs)
    for ( int ig = 1; ig <= n_grp; ig++ )
     {
      int h = isex(ig);
      isizeTrans = iYrIncChanges(h,YrRef);
      int m = imature(ig);
      int o = ishell(ig);
      h <= 1 ? lam = spr_lambda: lam = (1.0 - spr_lambda);
	  if(nmature==1)
       MMAState(nyr+i) += sum(lam * elem_prod(numbers_proj_gytl(ig,i,1), maturity(h)));
   	  if(nmature==2)
	   if(m==1)	  
        MMAState(nyr+i) += sum(lam * numbers_proj_gytl(ig,i,1));
      MLAState(nyr+i) += sum(lam * elem_prod(numbers_proj_gytl(ig,i,1), legal(h)));
     }
    // Compute the TAC
    //cout << "STATE " <<  MMAState(nyr+i)*MeanWState << " " << MLAState(nyr+i)*MeanWState << " " << MMAState(nyr+i)/MMARef << endl;
    if (MMAState(nyr+i) < 0.5*MMARef)
     StateTAC = 0;
    else
     if (MMAState(nyr+i) >= 0.5*MMARef & MMAState(nyr+i) < MMARef)
      {
       StateTAC = 0.1*(MMAState(nyr+i)/MMARef)*MMAState(nyr+i)*MeanWStateMature;
      }
     else
      {
       StateTAC = 0.1*MMAState(nyr+i)*MeanWStateMature;
      }
     TAC2 = 0.25*MLAState(nyr+i)*MeanWStateLegal;
     if (TAC2 < StateTAC) StateTAC = TAC2;
     // Adjust so that the TAC is not larger than the ABC
     if (FederalStuff(3) < StateTAC)
      { TACType = 1; TargetC = FederalStuff(2); }                    /// > Hit the total catch OFL
     else
      { TACType = 2; TargetC = StateTAC; }                           /// > Hit the retained catc OFL
     if (Apply_HCR_prj==1) cout << "TACS " <<  nyr+i << " Total ABC " << FederalStuff(2) << " Retained ABC " << FederalStuff(3) << " StateTAC " << StateTAC << " Final Decision: " << TACType << " " << TargetC << endl;
     // DO a projection for the current F
     log_fimpbarPass = log_fimpbar;
     d4_PassBack = project_one_year(i, iproj, YrRef, MoltProb, rtt, rec_sdd, Rec_use, d4_Pass);
     int NeedToTune;
     if (Apply_HCR_prj==1) NeedToTune = YES;
     if (Apply_HCR_prj==0) NeedToTune = NO;
     if (TACType==1 && catch_pass(2)-1.0e-5 < TargetC) NeedToTune = NO;
     if (TACType==2 && catch_pass(1)-1.0e-5 < TargetC) NeedToTune = NO;
     // Apply bisection to find the target F for the directed fishery
     if (NeedToTune==YES)
      {
       Fmin = 0; Fmax =1;
       for (int ii=1; ii<=20;ii++)
        {
         Fmult = (Fmin+Fmax)/2.0;
         for (int k=1;k<=nfleet;k++)
          if (Ffixed(k) != 1) log_fimpbarPass(k) = log(mfexp(log_fimpbar(k))*Fmult);
         d4_PassBack = project_one_year(i, iproj, YrRef, MoltProb, rtt, rec_sdd, Rec_use, d4_Pass);
         if (TACType == 1)
          {
           if (catch_pass(2) > TargetC) Fmax = Fmult; else Fmin = Fmult;
          }
         if (TACType == 2)
          {
           if (catch_pass(1) > TargetC) Fmax = Fmult; else Fmin = Fmult;
          }
        }
       cout << "CTUNE " << Fmult << " " << TargetC << " " << catch_pass << endl;
      }
     // Restore the N-matrix
     for ( int ig = 1; ig <= n_grp; ig++ )
      for ( int j = 2; j <= nseason; j++)
       numbers_proj_gytl(ig,i,j) = d4_PassBack(ig,1,j);
     if (i !=  iproj)
      for ( int ig = 1; ig <= n_grp; ig++ )
       numbers_proj_gytl(ig,i+1,1) = d4_PassBack(ig,2,1);
     ssb_prj(nyr+i) = ssb_pass;
    } // i
  // return
  ssb_pass = ssb_prj(nyr+iproj);
  return(ssb_prj);
}

dvar4_array model_parameters::project_one_year(const int i, const int iproj, const int YrRef, dvar_matrix MoltProb,
                                     dvar_matrix rtt, dvar_matrix  rec_sdd, dvar_vector Rec_use, dvar_matrix d4_Pass)
{
 {
  int isizeTrans;
  double xi;                                                               ///> discard mortality rate
  dvariable log_ftmp;
  dvar4_array numbers_proj_gytl(1,n_grp,1,2,1,nseason,1,nclass);           ///> Numbers-at-size
  dvar_vector x(1,nclass);                                                 ///> Temp vector for numbers
  dvar_vector y(1,nclass);                                                 ///> Temp vector for numbers
  dvar_vector z(1,nclass);                                                 ///> Temp vector for numbers
  dvar3_array _F1(1,nsex,1,nseason,1,nclass);                              ///> Fishing mortality
  dvar3_array _F2(1,nsex,1,nseason,1,nclass);                              ///> Fishing mortality
  dvar4_array _Z1(1,nsex,1,nmature,1,nseason,1,nclass);                              ///> Total mortality
  dvar4_array _Z2(1,nsex,1,nmature,1,nseason,1,nclass);                              ///> Total mortality
  dvar5_array _S(1,nsex,1,nmature,1,nseason,1,nclass,1,nclass);                      ///> Surival Rate (S=exp(-Z))
  dvar3_array _ft(1,nfleet,1,nsex,1,nseason);                              ///> Fishing mortality by gear
  dvar3_array d4_Npass(1,n_grp,1,nseason,1,nclass);                        ///> For passing out
  dvar_vector sel(1,nclass);                                               ///> Capture selectivity
  dvar_vector selret(1,nclass);                                            ///> Selectvity x retained
  dvar_vector ret(1,nclass);                                               ///> Retained probability
  dvar_vector vul(1,nclass);                                               ///> Total vulnerability
  dvar_vector nal(1,nclass);                                               ///> Numbers-at-length
  // Pass in
  numbers_proj_gytl.initialize();
  for ( int ig = 1; ig <= n_grp; ig++ ) numbers_proj_gytl(ig,1,1) = d4_Pass(ig);
  // Initialize the Fs
  _F1.initialize();
  for ( int h = 1; h <= nsex; h++ )
   for ( int j = 1; j <= nseason; j++ )
    for ( int l = 1; l <= nclass; l++)
     _F2(h,j,l) = 1.0e-10;
  _ft.initialize();
  for ( int k = 1; k <= nfleet; k++ )
   for ( int h = 1; h <= nsex; h++ )
    for ( int j = 1; j <= nseason; j++ )
     if ( fhit(YrRef,j,k) )
      {
       log_ftmp = log_fimpbarPass(k);
       if (h==2) log_ftmp += log_foff(k);
       _ft(k,h,j) = mfexp(log_ftmp);
       xi = dmr(YrRef,k);                                                 // Discard mortality rate
       sel = mfexp(log_slx_capture(k,h,YrRef))+1.0e-10;                          // Selectivity
       ret = mfexp(log_slx_retaind(k,h,YrRef)) * slx_nret(h,k);                  // Retension
       vul = elem_prod(sel, ret + (1.0 - ret) * xi);                             // Vulnerability
       _F1(h,j) += _ft(k,h,j) * vul;
       _F2(h,j) += _ft(k,h,j) * sel;
     }
  // computer the total mortality
  _Z1.initialize();  _Z2.initialize(); _S.initialize();
  for( int m =1; m <= nmature; m++)
  for ( int h = 1; h <= nsex; h++ )
   for ( int j = 1; j <= nseason; j++ )
    {
     _Z1(h,m,j) = (m_prop(YrRef,j) * M(h,m,1,YrRef)) + _F1(h,j);
     _Z2(h,m,j) = (m_prop(YrRef,j) * M(h,m,1,YrRef)) + _F2(h,j);
     if (season_type(j) == 0) for ( int l = 1; l <= nclass; l++ ) _S(h,m,j)(l,l) = 1.0-_Z1(h,m,j,l)/_Z2(h,m,j,l)*(1.0-mfexp(-_Z2(h,m,j,l)));
     if (season_type(j) == 1) for ( int l = 1; l <= nclass; l++ ) _S(h,m,j)(l,l) = mfexp(-_Z1(h,m,j,l));
    }
  // Update the dynamics
  for ( int j = 1; j <= nseason; j++ )
   {
    for ( int ig = 1; ig <= n_grp; ig++ )
     {
      int h = isex(ig);
      isizeTrans = iYrIncChanges(h,YrRef);
      int m = imature(ig);
      int o = ishell(ig);
      x = numbers_proj_gytl(ig,1,j);
      // Mortality (natural and fishing)
      x = x * _S(h,m,j);
    if ( nshell == 1 )
     {
	 if(nmature == 1)
	 {
		  // Molting and growth
        if (j == season_growth)
         {
          y = elem_prod(x, 1 - MoltProb(h)); // did not molt, become oldshell
          x = elem_prod(x, MoltProb(h)) * growth_transition(h,isizeTrans); // molted and grew, stay newshell
          x += y;
         }
        // Recruitment
        if (j == season_recruitment)
         {
          if (IsProject==NOPROJECT) x += rtt(h);
          if (IsProject==PROJECT) x += Rec_use(h)*rec_sdd(h);
         }
        if (j == nseason)
         {
          if (i != iproj) numbers_proj_gytl(ig,2,1) = x;
         }
        else
         numbers_proj_gytl(ig,1,j+1) = x;
	  }
      if(nmature == 2)
		{
		  if ( m == 1 ) // mature
          {
           //No molting, growth, or recruitment for mature animals
          if (j == nseason)
           {
            if (i != iproj) numbers_proj_gytl(ig,2,1) = x;
           }
           else
            numbers_proj_gytl(ig,1,j+1) = x;
          }
          if ( m == 2 ) // immature
          {
          // Molting and growth
           z.initialize();
           if (j == season_growth)
            {
             //z = elem_prod(x, molt_probability(h)(i)) * growth_transition(h,isizeTrans); 		// molted to maturity
             //x = elem_prod(x, 1 - molt_probability(h)(i)) * growth_transition(h,isizeTrans);    // molted, but immature
			 z = elem_prod(x * growth_transition(h,isizeTrans), MoltProb(h)) ; 		// molted to maturity
             x = elem_prod(x * growth_transition(h,isizeTrans), 1 - MoltProb(h)) ;    // molted, but immature
            }
		   if (j == season_recruitment)
            {
			 if (IsProject==NOPROJECT) x += rtt(h);
			 if (IsProject==PROJECT) x += Rec_use(h)*rec_sdd(h);
			}
		   if (j == nseason)
			{
			if (i != iproj) {numbers_proj_gytl(ig-1,2,1) += z; numbers_proj_gytl(ig,2,1) = x;}
			}
			else
			{numbers_proj_gytl(ig-1,1,j+1) += z; numbers_proj_gytl(ig,1,j+1) = x;}
          }	 
		}
       }
      else
       {
        if ( o == 1 ) // newshell
         {
          // Molting and growth
          if (j == season_growth)
           {
            y = elem_prod(x, 1 - MoltProb(h)); // did not molt, become oldshell
            x = elem_prod(x, MoltProb(h)) * growth_transition(h,isizeTrans); // molted and grew, stay newshell
           }
          // Recruitment
          if (j == season_recruitment)
           {
            if (IsProject==NOPROJECT) x += rtt(h);
            if (IsProject==PROJECT) x += Rec_use(h)*rec_sdd(h);
           }
          if (j == nseason)
           {
            if (i != iproj)
             numbers_proj_gytl(ig,2,1) = x;
           }
          else
           numbers_proj_gytl(ig,1,j+1) = x;
         }
        if ( o == 2 ) // oldshell
         {
          // Molting and growth
          if (j == season_growth)
           {
            z = elem_prod(x, MoltProb(h)) * growth_transition(h,isizeTrans); // molted and grew, become newshell
            x = elem_prod(x, 1 - MoltProb(h)) + y; // did not molt, remain oldshell and add the newshell that become oldshell
           }
          if (j == nseason)
           {
            if (i != iproj)
             { numbers_proj_gytl(ig-1,2,1) += z; numbers_proj_gytl(ig,2,1) = x; }
           }
          else
          { numbers_proj_gytl(ig-1,1,j+1) += z; numbers_proj_gytl(ig,1,j+1) = x; }
         } // oldshell
       } // nshell = 2
     } // ig
   } // j
  // Project SSB
  ssb_pass = 0;
  for ( int ig = 1; ig <= n_grp; ig++ )
   {
    int h = isex(ig);
    int o = ishell(ig);
    int m = imature(ig);
    double lam;
    h <= 1 ? lam = spr_lambda: lam = (1.0 - spr_lambda);
	if(nmature==1)
     ssb_pass += lam * numbers_proj_gytl(ig,1,season_ssb) * elem_prod(mean_wt(h,YrRef), maturity(h));
	if(nmature==2)
     if(m==1)
		ssb_pass += lam * numbers_proj_gytl(ig,1,season_ssb) * mean_wt(h,YrRef);
   }
  for ( int j = 1; j <= nseason; j++ )
   for ( int ig = 1; ig <= n_grp; ig++ )
    d4_Npass(ig,j) = numbers_proj_gytl(ig,1,j);
  catch_pass = calc_predicted_project(nyr, d4_Npass, _ft, _Z1, _Z2);
  return(numbers_proj_gytl);
 }
}

dvar_vector model_parameters::calc_predicted_project(const int YrRef, dvar3_array d4_Npass, dvar3_array _ft, dvar4_array _Z1, dvar4_array _Z2)
{
 {
  //int h,i,j,k,ig,type,unit;
  double xi;                                                               ///> Discard rate
  dvar_vector out(1,2+nfleet);                                             ///> Output
  dvariable tmp_ft,out2;                                                   ///> Temp
  dvar_vector sel(1,nclass);                                               ///> Capture selectivity
  dvar_vector selret(1,nclass);                                            ///> Selectvity x retained
  dvar_vector ret(1,nclass);                                               ///> Retained probability
  dvar_vector vul(1,nclass);                                               ///> Total vulnerability
  dvar_vector nal(1,nclass);                                               ///> Numbers-at-length
  dvar_vector tempZ1(1,nclass);                                            ///> total mortality
  // out(1): retained catch
  // out(2): dead total catch
  // out(2+k): dead animals
  out.initialize();
  for ( int m = 1; m <= nmature; m++ )
   for ( int h = 1; h <= nsex; h++ )
    for ( int j = 1; j <= nseason; j++ )
    {
     nal.initialize();
     for ( int o = 1; o <= nshell; o++ )
      { int ig = pntr_hmo(h,m,o); nal += d4_Npass(ig)(j); }
      nal = elem_prod(nal, mean_wt(h)(YrRef));
      for ( int k = 1; k <= nfleet; k++ )
       {
        xi = dmr(YrRef,k);                                                ///> Discard mortality rate
        sel = mfexp(log_slx_capture(k,h,YrRef))+1.0e-10;                  ///> Selectivity
        ret = mfexp(log_slx_retaind(k,h,YrRef)) * slx_nret(h,k);          ///> Retension
        vul = elem_prod(sel, ret + (1.0 - ret) * xi);                     ///> Vulnerability
        selret = elem_prod(sel,ret);
        if (season_type(j)==0) tempZ1 = _Z1(h,m,j); else tempZ1 = _Z2(h,m,j);
        out(1) += nal * elem_div(elem_prod(_ft(k,h,j) * selret, 1.0 - mfexp(-tempZ1)), tempZ1);
        // Total dead
        out(2) += nal * elem_div(elem_prod(_ft(k,h,j) * vul, 1.0 - mfexp(-tempZ1)), tempZ1);
        // fleet-specific dead crab
        out(2+k) += nal * elem_div(elem_prod(_ft(k,h,j) * vul, 1.0 - mfexp(-tempZ1)), tempZ1);
       }
    }
  return(out);
 }
}

dvar_vector model_parameters::compute_OFL_and_ABC(const int iyr, dvar_matrix d4_Npass)
{
 {
  int IsProjectSave;                                                 ///> Variable to save the projection pointer
  dvar_vector Bproj(1,1);                                            ///> Projected biomass (one year)
  dvar_vector return_vec(1,3);                                       ///> Material to return
  dvariable Fmsy, Bmsy, Fmult2, FF;                                  ///> Teps
  IsProjectSave = IsProject;
  IsProject = NOPROJECT;
  // Extract reference points
  Fmsy = 1; Bmsy = spr_bmsy;
  // Set F to Fmsy (by fleet)
  log_fimpbarOFL = log(sd_fmsy);
  Bproj = project_biomass_OFL(nyr, 1,d4_Npass);
  if (ssb_pass < Bmsy & ssb_pass >= OFLbeta * Bmsy)
   {
    // Adjust F if below target since it's a function biomass needs to be interated
    for( int iloop = 1; iloop <= 10; iloop++)
     {
      Fmult2 = Fmsy * (ssb_pass / Bmsy - OFLalpha) / (1 - OFLalpha);
      if (Fmult2 < 0.1*FF)
       FF = 0.1*FF;
      else
       FF = Fmult2;
      if (FF < 0.00001) FF = 0.00001;
      //cout << "TuneB " << Fmsy << " " << FF << " " << ssb_pass << " " << ssb_pass/Bmsy << " " << ssb_pass/ssbF0 <<endl;
      for (int k=1;k<=nfleet;k++) if (Ffixed(k) != 1) log_fimpbarOFL(k) = log(sd_fmsy(k)*FF);
      Bproj = project_biomass_OFL(nyr,1,d4_Npass);
     }
   }
  if (ssb_pass < OFLbeta * Bmsy)
   {
    FF = 1.0e-10;
    for (int k=1;k<=nfleet;k++) if (Ffixed(k) != 1) log_fimpbarOFL(k) = log(sd_fmsy(k)*FF);
    Bproj = project_biomass_OFL(nyr,1,d4_Npass);
   }
  // save the OFL
  return_vec(1) = ofltot_pass;
  return_vec(2) = ofltot_pass*ABCBuffer;
  return_vec(3) = oflret_pass*ABCBuffer;
  IsProject = IsProjectSave;                                         ///> Return back to normal
  return(return_vec);
 }
}

dvar_vector model_parameters::project_biomass_OFL(const int YrRef, const int iproj, dvar_matrix d4_Npass)
{
  int isizeTrans;                                                          ///> Size-transition matrix
  dvariable log_ftmp;                                                      ///> Temp
  double xi;                                                               ///> Discard mortality
  dvar_matrix rtt(1,nsex,1,nclass);                                        ///> Constant recruitment
  dvar_vector x(1,nclass);                                                 ///> Temp vector for numbers
  dvar_vector y(1,nclass);                                                 ///> Temp vector for numbers
  dvar_vector z(1,nclass);                                                 ///> Temp vector for numbers
  dvar3_array _F1(1,nsex,1,nseason,1,nclass);                              ///> Fishing mortality
  dvar3_array _F2(1,nsex,1,nseason,1,nclass);                              ///> Fishing mortality
  dvar4_array _Z1(1,nsex,1,nmature,1,nseason,1,nclass);                              ///> Total mortality
  dvar4_array _Z2(1,nsex,1,nmature,1,nseason,1,nclass);                              ///> Total mortality
  dvar5_array _S(1,nsex,1,nmature,1,nseason,1,nclass,1,nclass);                      ///> Surival Rate (S=exp(-Z))
  dvar3_array _ft(1,nfleet,1,nsex,1,nseason);                              ///> Fishing mortality by gear
  dvar4_array numbers_proj_gytl(1,n_grp,1,iproj,1,nseason,1,nclass);       ///> N matrix
  dvar3_array d4_Npass_2(1,n_grp,1,nseason,1,nclass);                      ///> Pass variable
  dvar_vector sel(1,nclass);                                               ///> Capture selectivity
  dvar_vector ret(1,nclass);                                               ///> Retained probability
  dvar_vector vul(1,nclass);                                               ///> Total vulnerability
  dvar_vector nal(1,nclass);                                               ///> Numbers-at-length
  dvar_vector out(1,2+nfleet);                                             ///> Output
  // Copy N from the end of the assessment into the first projection year
  numbers_proj_gytl.initialize();
  for ( int ig = 1; ig <= n_grp; ig++ )
   numbers_proj_gytl(ig)(1)(1) = d4_Npass(ig);
  dvar_matrix MoltProb(1,nsex,1,nclass);
  for (int h = 1; h <= nsex; h++ )
   for (int l=1;l<=nclass;l++)
    MoltProb(h,l) = molt_probability(h,YrRef,l);
  // recruitment distribution
  if (nsex>1)
   {
    rtt(1) = spr_rbar / 2.0 * rec_sdd(1);
    rtt(2) = spr_rbar / 2.0 * rec_sdd(2);
   }
  else
   rtt(1) = spr_rbar * rec_sdd(1);
  // Initialize the Fs
  _F1.initialize();
  for ( int h = 1; h <= nsex; h++ )
   for ( int j = 1; j <= nseason; j++ )
    for ( int l = 1; l <= nclass; l++)
     _F2(h,j,l) = 1.0e-10;
  _ft.initialize();
  for ( int k = 1; k <= nfleet; k++ )
   for ( int h = 1; h <= nsex; h++ )
    for ( int j = 1; j <= nseason; j++ )
     if ( fhit(YrRef,j,k) )
      {
       log_ftmp = log_fimpbarOFL(k);
       if (h==2) log_ftmp += log_foff(k);
       _ft(k,h,j) = mfexp(log_ftmp);
       xi = dmr(YrRef,k);                                                        // Discard mortality rate
       sel = mfexp(log_slx_capture(k,h,YrRef))+1.0e-10;                          // Selectivity
       ret = mfexp(log_slx_retaind(k,h,YrRef)) * slx_nret(h,k);                  // Retension
       vul = elem_prod(sel, ret + (1.0 - ret) * xi);                             // Vulnerability
       _F1(h,j) += _ft(k,h,j) * vul;
       _F2(h,j) += _ft(k,h,j) * sel;
     }
  // computer the total mortality
  _Z1.initialize();  _Z2.initialize(); _S.initialize();
  for( int m = 1; m <=nmature; m++)
  for ( int h = 1; h <= nsex; h++ )
   for ( int j = 1; j <= nseason; j++ )
    {
     _Z1(h,m,j) = (m_prop(YrRef,j) * M(h,m,YrRef)) + _F1(h,j);
     _Z2(h,m,j) = (m_prop(YrRef,j) * M(h,m,YrRef)) + _F2(h,j);
     if (season_type(j) == 0) for ( int l = 1; l <= nclass; l++ ) _S(h,m,j)(l,l) = 1.0-_Z1(h,m,j,l)/_Z2(h,m,j,l)*(1.0-mfexp(-_Z2(h,m,j,l)));
     if (season_type(j) == 1) for ( int l = 1; l <= nclass; l++ ) _S(h,m,j)(l,l) = mfexp(-_Z1(h,m,j,l));
    }
  // Now project(usually for 1 year)
  for ( int i = 1; i <= iproj; i++ )
   {
    for ( int j = 1; j <= nseason; j++ )
     for ( int ig = 1; ig <= n_grp; ig++ )
      {
       int h = isex(ig);
       isizeTrans = iYrIncChanges(h,YrRef);
       int m = imature(ig);
       int o = ishell(ig);
       x = numbers_proj_gytl(ig,i,j);
       // Mortality (natural and fishing)
       x = x * _S(h,m,j);
      if ( nshell == 1 )
       {
	   if(nmature == 1)
	    {
	    // Molting and growth
         if (j == season_growth)
          {
           y = elem_prod(x, 1 - MoltProb(h)); // did not molt, become oldshell
           x = elem_prod(x, MoltProb(h)) * growth_transition(h,isizeTrans); // molted and grew, stay newshell
           x += y;
          }
         // Recruitment
         if (j == season_recruitment) x += rtt(h);
         if (j == nseason)
          {
           if (i != iproj) numbers_proj_gytl(ig)(i+1)(1) = x;
          }
         else
           numbers_proj_gytl(ig)(i)(j+1) = x;
	    }
      if(nmature == 2)
		{
		  if ( m == 1 ) // mature
          {
           //No molting, growth, or recruitment for mature animals
          if (j == nseason)
          {
           if (i != iproj) numbers_proj_gytl(ig)(i+1)(1) = x;
          }
          else
           numbers_proj_gytl(ig)(i)(j+1) = x;
          }
          if ( m == 2 ) // immature
          {
          // Molting and growth
           z.initialize();
           if (j == season_growth)
            {
             //z = elem_prod(x, molt_probability(h)(i)) * growth_transition(h,isizeTrans); 		// molted to maturity
             //x = elem_prod(x, 1 - molt_probability(h)(i)) * growth_transition(h,isizeTrans);    // molted, but immature
			 z = elem_prod(x * growth_transition(h,isizeTrans), MoltProb(h)) ; 		// molted to maturity
             x = elem_prod(x * growth_transition(h,isizeTrans), 1 - MoltProb(h)) ;    // molted, but immature
            }
           if (j == season_recruitment) x += rtt(h);
		   if (j == nseason)
			{
			if (i != iproj) {numbers_proj_gytl(ig-1,i+1,1) += z; numbers_proj_gytl(ig,i+1,1) = x;}
			}
			else
			{numbers_proj_gytl(ig-1,i,j+1) += z; numbers_proj_gytl(ig,i,j+1) = x;}
          }	 
		}
        }
       else
        {
         if ( o == 1 ) // newshell
          {
           // Molting and growth
           if (j == season_growth)
            {
              y = elem_prod(x, 1 - MoltProb(h)); // did not molt, become oldshell
              x = elem_prod(x, MoltProb(h)) * growth_transition(h,isizeTrans); // molted and grew, stay newshell
            }
           // Recruitment
           if (j == season_recruitment) x += rtt(h);
           if (j == nseason)
            {
             if (i != iproj)
              numbers_proj_gytl(ig)(i+1)(1) = x;
            }
           else
            numbers_proj_gytl(ig)(i)(j+1) = x;
          }
         if ( o == 2 ) // oldshell
          {
           // Molting and growth
           z.initialize();
           if (j == season_growth)
            {
             z = elem_prod(x, MoltProb(h)) * growth_transition(h,isizeTrans); // molted and grew, become newshell
             x = elem_prod(x, 1 - MoltProb(h)) + y; // did not molt, remain oldshell and add the newshell that become oldshell
            }
           if (j == nseason)
            {
             if (i != iproj)
              { numbers_proj_gytl(ig-1)(i+1)(1) += z; numbers_proj_gytl(ig)(i+1)(1) = x; }
             }
            else
             { numbers_proj_gytl(ig-1)(i)(j+1) += z; numbers_proj_gytl(ig)(i)(j+1) = x; }
         } // oldshell
       } // nshell = 2
      } // j
    } // i
  dvar_vector ssb(1,iproj);
  ssb.initialize();
  for ( int i = 1; i <= iproj; i++ )
   for ( int ig = 1; ig <= n_grp; ig++ )
    {
     int h = isex(ig);
     int o = ishell(ig);
     int m = imature(ig);
     double lam;
     h <= 1 ? lam = spr_lambda: lam = (1.0 - spr_lambda);
	 if(nmature==1)
      ssb(i) += lam * numbers_proj_gytl(ig)(i)(season_ssb) * elem_prod(mean_wt(h)(YrRef), maturity(h));
     if(nmature==2)
	  if(m == 1)
		ssb(i) += lam * numbers_proj_gytl(ig)(i)(season_ssb) * mean_wt(h)(YrRef); 
    }
   //cout<<"mean_wt"<<mean_wt<<endl;
   //cout<<"numbers proj"<<numbers_proj_gytl<<endl;
  // return material
  ssb_pass = ssb(iproj);
  for ( int j = 1; j <= nseason; j++ )
   for ( int ig = 1; ig <= n_grp; ig++ )
    d4_Npass_2(ig,j) = numbers_proj_gytl(ig)(iproj)(j);
  out = calc_predicted_project(nyr, d4_Npass_2, _ft, _Z1, _Z2);
  oflret_pass = out(1); ofltot_pass = out(2);
  return(ssb);
}

void model_parameters::calc_spr_reference_points2(const int DoProfile)
{
  int iproj;
  dvar_matrix equilibrium_numbers(1,n_grp,1,nclass);
  dvariable FF;
  dvariable Fmsy;
  dvariable MeanF,NF;
  dvariable Fmult, Fmult2, SSBV0, SSBV1a,SSBV1b,Deriv, Adjust, R1;
  dvariable SteepMin,SteepMax;
  dvar_vector Fave(1,nfleet);
  dvar_matrix d4_Npass(1,n_grp,1,nclass);       ///> Numbers-at-sex/mature/shell/length.
  dvar_vector tst(1,3);
  bSteadyState = REFPOINTS;
  IsProject = NOPROJECT;
  iproj = 1;
  dvar_vector Bproj(1,iproj);
  Eqn_basis = CONSTANTREC;
  // Find mean recruitment
  if (nsex==1) spr_rbar = mean(recruits(1)(spr_syr,spr_nyr));
  if (nsex==2) spr_rbar = mean(recruits(1)(spr_syr,spr_nyr))+mean(recruits(2)(spr_syr,spr_nyr));
  // Find the average F by fleet over the last 4 years
  for (int k = 1; k <= nfleet; k++)
   {
    MeanF = 0; NF = 0;
    for (int i = spr_aveF_syr; i <= spr_aveF_nyr; i++) { MeanF += fout(k,i); NF += 1; }
    Fave(k) = (MeanF+1.0e-10)/NF;
   }
 // cout<<"going into Bzero calc"<<endl;
  // Find SSB for F=0 for all fleets
  for (int k=1;k<=nfleet;k++) log_fimpbar(k) = -100;
   equilibrium_numbers = calc_brute_equilibrium(SexR_syr,SexR_nyr,nyr,200);
  ssbF0 = ssb_pass;
 // cout<<"coming out of Bzero calc"<<endl;
  //cout<<"Bzereo"<<ssbF0<<endl;
  // Solve for F35% and hence the Fmsy proxy (Tier 3 analysis)
  if (OFLTier==3)
   {
   cout<<"goin in F35 calc"<<endl;
    // Find Fmsy (=F35%) when adjusting the Fs for some fleets
    for (int k=1;k<=nfleet;k++) log_fimpbar(k) = log(Fave(k));
    Fmult = 1.0;
    for (int i=1;i<=10;i++)
     {
		// cout<<"log_fimpbar1 "<<log_fimpbar<<endl;
		 // Set F
      for (int k=1;k<=nfleet;k++)
       if (Ffixed(k) != 1) log_fimpbar(k) = log(Fave(k)*Fmult);
      equilibrium_numbers = calc_brute_equilibrium(SexR_syr,SexR_nyr,nyr,200);
      SSBV0 = ssb_pass/ssbF0-spr_target;
		// cout<<"log_fimpbar1 "<<log_fimpbar<<endl;
      for (int k=1;k<=nfleet;k++)
       if (Ffixed(k) != 1) log_fimpbar(k) = log(Fave(k)*(Fmult+0.001));
      equilibrium_numbers = calc_brute_equilibrium(SexR_syr,SexR_nyr,nyr,200);
      SSBV1a = ssb_pass/ssbF0-spr_target;
      for (int k=1;k<=nfleet;k++)
       if (Ffixed(k) != 1) log_fimpbar(k) = log(Fave(k)*(Fmult-0.001));
      equilibrium_numbers = calc_brute_equilibrium(SexR_syr,SexR_nyr,nyr,200);
      SSBV1b = ssb_pass/ssbF0-spr_target;
      Deriv = (SSBV1a-SSBV1b)/0.002;
      Fmult2 = Fmult - SSBV0/Deriv;
      if (Fmult2 < 0.01) Fmult2 = 0.01;
      if (Fmult2 < 0.1*Fmult)
       Fmult = 0.1*Fmult;
      else
       Fmult = Fmult2;
   		// cout<<"log_fimpbar2 "<<log_fimpbar<<endl;
	    // cout<<"ssb_pass/ssbF0 "<<ssb_pass/ssbF0<<endl;
	    // cout<<"SSBV0 "<<SSBV0<<endl;
	    // cout<<"SSBV1a "<<SSBV1a<<endl;
	    // cout<<"SSBV1b "<<SSBV1b<<endl;
	    // cout<<"Deriv "<<Deriv<<endl;
	    // cout<<"Fmult "<<Fmult<<endl;
     }
     //cout<<"Fave "<<Fave<<endl;
     //cout<<"Fmult "<<Fmult<<endl;
    for (int k=1;k<=nfleet;k++)
     if (Ffixed(k) != 1) log_fimpbar(k) = log(Fave(k)*Fmult);
   // cout<<"log_fimpbar "<<log_fimpbar<<endl;
    equilibrium_numbers = calc_brute_equilibrium(SexR_syr,SexR_nyr,nyr,200);
    Bmsy = ssb_pass;
   }
  // cout<<"out FMSY"<<endl;
  // Tier 4 control rule
  if (OFLTier==4)
   {
    // BMSY is the mean SSB over a set of years
    Bmsy = mean(calc_ssb()(spr_syr,spr_nyr));
    Fmsy = OFLgamma * M0(1);
    for (int k=1;k<=nfleet;k++) log_fimpbar(k) = log(Fave(k));
    for (int k=1;k<=nfleet;k++)
     if (Ffixed(k) != 1) log_fimpbar(k) = log(Fmsy);
   }
  // Save FMSY
  for (int k=1;k<=nfleet;k++) sd_fmsy(k) = mfexp(log_fimpbar(k));
  // Store reference points
  Fmsy = 1;
  spr_bmsy = Bmsy;
  // Store the N from the last year
  for ( int ig = 1; ig <= n_grp; ig++ ) d4_Npass(ig) = d4_N(ig)(nyr+1)(1);
   cout<<"projecting biomass ofl"<<endl;
   // Base projections on last-year biological and fishery parameters
  log_fimpbarOFL = log(sd_fmsy);
  Bproj = project_biomass_OFL(nyr, iproj,d4_Npass);
  spr_fofl = 1.0;
  spr_depl = ssb_pass / Bmsy;
  cout<<"projected biomass ofl"<<endl;
  if (ssb_pass < Bmsy & ssb_pass >= OFLbeta * Bmsy)
   {
    // Adjust F if below target since it's a function biomass needs to be interated
    for( int iloop = 1; iloop <= 10; iloop++)
     {
      Fmult2 = Fmsy * (ssb_pass / Bmsy - OFLalpha) / (1 - OFLalpha);
      if (Fmult2 < 0.1*FF)
       FF = 0.1*FF;
      else
       FF = Fmult2;
      if (FF < 0.00001) FF = 0.00001;
      //cout << "TuneA " << Fmsy << " " << FF << " " << ssb_pass << " " << ssb_pass/Bmsy << " " << ssb_pass/ssbF0 <<endl;
      for (int k=1;k<=nfleet;k++) if (Ffixed(k) != 1) log_fimpbarOFL(k) = log(sd_fmsy(k)*FF);
      Bproj = project_biomass_OFL(nyr,iproj,d4_Npass);
     }
    spr_fofl = FF/Fmsy;
    spr_depl = ssb_pass / Bmsy;
   }
  if (ssb_pass < OFLbeta * Bmsy)
   {
    FF = 1.0e-10;
    for (int k=1;k<=nfleet;k++) if (Ffixed(k) != 1) log_fimpbarOFL(k) = log(sd_fmsy(k)*FF);
    Bproj = project_biomass_OFL(nyr,iproj,d4_Npass);
    spr_fofl = FF/Fmsy;
    spr_depl = ssb_pass / Bmsy;
   }
  cout<<"Did FOFL"<<endl;
  // save fofl
  for (int k=1;k<=nfleet;k++) sd_fofl(k) = mfexp(log_fimpbarOFL(k));
  // save the OFL
  spr_cofl = ofltot_pass;
  // Continue only calc_MSY is YES
  if (Calc_MSY == YES && (Stock_rec_prj==RICKER || Stock_rec_prj==BEVHOLT))
   {
	cout<<"In calc MSY"<<endl;
    // Find Steepness and R0
    Eqn_basis = STOCKRECREC;
    log_fimpbar = log(sd_fmsy);
    SteepMin = 0.2; SteepMax = 5.0;
    for (int ii=1;ii<=30;ii++)
     {
      Steepness = SteepMin+(SteepMax-SteepMin)/29.0*float(ii-1);
      if (Stock_rec_prj==RICKER)
       {
        SR_alpha_prj = spr_rbar/ssbF0*exp(log(5.0*Steepness)/0.8);
        SR_beta_prj = log(5.0*Steepness)/(0.8*ssbF0);
       }
      if (Stock_rec_prj==BEVHOLT)
       {
        SR_alpha_prj = 4.0*Steepness*spr_rbar/(5*Steepness-1.0);
        SR_beta_prj = (1.0-Steepness)*ssbF0/(5*Steepness-1.0);
       }
      for (int k=1;k<=nfleet;k++)
       if (Ffixed(k) != 1) log_fimpbar(k) = log(sd_fmsy(k)*1.001);
      equilibrium_numbers = calc_brute_equilibrium(SexR_syr,SexR_nyr,nyr,200);
      SSBV1a = oflret_pass;
      for (int k=1;k<=nfleet;k++)
       if (Ffixed(k) != 1) log_fimpbar(k) = log(sd_fmsy(k)*0.999);
      equilibrium_numbers = calc_brute_equilibrium(SexR_syr,SexR_nyr,nyr,200);
      SSBV1b = oflret_pass;
      Deriv = (SSBV1a-SSBV1b)/0.002;
      if (Deriv > 0)
       {
        SteepMin = Steepness - (SteepMax-SteepMin)/29.0;
        SteepMax = Steepness + (SteepMax-SteepMin)/29.0;
        ii = 40;
       }
     }
    //SteepMin = 0.2; SteepMax = 5.0;
    for (int ii=1;ii<=30;ii++)
     {
      Steepness = (SteepMin+SteepMax)/2.0;
      if (Stock_rec_prj==RICKER)
       {
        SR_alpha_prj = spr_rbar/ssbF0*exp(log(5.0*Steepness)/0.8);
        SR_beta_prj = log(5.0*Steepness)/(0.8*ssbF0);
       }
      if (Stock_rec_prj==BEVHOLT)
       {
        SR_alpha_prj = 4.0*Steepness*spr_rbar/(5*Steepness-1.0);
        SR_beta_prj = (1.0-Steepness)*ssbF0/(5*Steepness-1.0);
       }
      for (int k=1;k<=nfleet;k++)
       if (Ffixed(k) != 1) log_fimpbar(k) = log(sd_fmsy(k)*1.001);
      equilibrium_numbers = calc_brute_equilibrium(SexR_syr,SexR_nyr,nyr,200);
      SSBV1a = oflret_pass;
      for (int k=1;k<=nfleet;k++)
       if (Ffixed(k) != 1) log_fimpbar(k) = log(sd_fmsy(k)*0.999);
      equilibrium_numbers = calc_brute_equilibrium(SexR_syr,SexR_nyr,nyr,200);
      SSBV1b = oflret_pass;
      Deriv = (SSBV1a-SSBV1b)/0.002;
      if (Deriv < 0) SteepMin = Steepness; else SteepMax = Steepness;
     }
    cout << Steepness << " " << Deriv << " " << ssbF0 << endl;
    if (Stock_rec_prj==RICKER)
     {
      SR_alpha_prj = spr_rbar/ssbF0*exp(log(5.0*Steepness)/0.8);
      SR_beta_prj = log(5.0*Steepness)/(0.8*ssbF0);
     }
    if (Stock_rec_prj==BEVHOLT)
     {
      SR_alpha_prj = 4.0*Steepness*spr_rbar/(5*Steepness-1.0);
      SR_beta_prj = (1.0-Steepness)*ssbF0/(5*Steepness-1.0);
     }
    log_fimpbar = log(sd_fmsy);
    equilibrium_numbers = calc_brute_equilibrium(SexR_syr,SexR_nyr,nyr,200);
    Adjust = spr_bmsy/ssb_pass;
    if (Stock_rec_prj==RICKER)
     {
      SR_alpha_prj = spr_rbar/ssbF0*exp(log(5.0*Steepness)/0.8);
      SR_beta_prj = log(5.0*Steepness)/(0.8*ssbF0*Adjust);
     }
    if (Stock_rec_prj==BEVHOLT)
     {
      SR_alpha_prj = 4.0*Steepness*spr_rbar*Adjust/(5*Steepness-1.0);
      SR_beta_prj = (1.0-Steepness)*ssbF0*Adjust/(5*Steepness-1.0);
     }
    // Find SSB for F=0 for all fleets
    for (int k=1;k<=nfleet;k++) log_fimpbar(k) = -100;
    equilibrium_numbers = calc_brute_equilibrium(SexR_syr,SexR_nyr,nyr,200);
    ssbF0 = ssb_pass;
    // Check derivative
    log_fimpbar = log(sd_fmsy);
    for (int k=1;k<=nfleet;k++)
     if (Ffixed(k) != 1) log_fimpbar(k) = log(sd_fmsy(k)*1.001);
    equilibrium_numbers = calc_brute_equilibrium(SexR_syr,SexR_nyr,nyr,200);
    SSBV1a = oflret_pass;
    for (int k=1;k<=nfleet;k++)
     if (Ffixed(k) != 1) log_fimpbar(k) = log(sd_fmsy(k)*0.999);
    equilibrium_numbers = calc_brute_equilibrium(SexR_syr,SexR_nyr,nyr,200);
    SSBV1b = oflret_pass;
    Deriv = (SSBV1a-SSBV1b)/0.002;
    log_fimpbar = log(sd_fmsy);
    equilibrium_numbers = calc_brute_equilibrium(SexR_syr,SexR_nyr,nyr,200);
    cout << ssb_pass/ssbF0 << " " << ssb_pass/spr_bmsy << " " << exp(log_fimpbar) << " " << oflret_pass << " " << Steepness << " " << Deriv << " " << ssbF0 << " " << spr_bmsy << endl;
    if (Compute_yield_prj==YES & DoProfile==YES)
     for (int ii=0;ii<=100;ii++)
      {
       if (ii==0) FF = 1.0e-10; else FF = float(ii)/20;
       for (int k=1;k<=nfleet;k++) if (Ffixed(k) != 1) log_fimpbar(k) = log(sd_fmsy(k)*FF);
       equilibrium_numbers = calc_brute_equilibrium(SexR_syr,SexR_nyr,nyr,200);
       spr_yield(ii,1) = ssb_pass/ssbF0;
       spr_yield(ii,2) = ssb_pass/spr_bmsy;
       spr_yield(ii,3) = exp(log_fimpbar(1));
       spr_yield(ii,4) = oflret_pass;
      }
   }
  /**
   * @brief Conduct projections
  **/
}

void model_parameters::write_eval(void)
{
  int index;                                                         ///> Counters
  dvariable MeanF,NF,Fmult,Bmsy_out,eps1;                            ///> Temp variables
  dvar_vector Bproj(syr,nyr+nproj);                                  ///> Biomass outout
  dvar_vector Fave(1,nfleet);                                        ///> Average F
  // Darcy MCMC output
  MCout(theta);
  // Header
  if (NfunCall==1)
   {
   }
  /**
   * @brief calculate sd_report variables in final phase
  **/
 calc_spr_reference_points2(0);
 cout<<"Calced spr refs"<<endl;
 mcoutSSB << calc_ssb() << endl;
 if (nsex==1) mcoutREC << recruits(1) << endl;
 if (nsex==2) mcoutREC << recruits(1)+recruits(2) << endl;
 mcoutREF << NfunCall << " " << spr_rbar << " " << ssbF0 << " " << spr_bmsy << " " << spr_depl << " " << spr_cofl << " " << sd_fmsy << " " << sd_fofl << endl;
 // Find the average F by fleet over the last 4 years
 for (int k = 1; k <= nfleet; k++)
  {
   MeanF = 0; NF = 0;
   for (int i = spr_aveF_syr; i <= spr_aveF_nyr; i++) { MeanF += fout(k,i); NF += 1; }
   Fave(k) = (MeanF+1.0e-10)/NF;
  }
  cout<<"Setting Fs"<<endl;
 // Set the average Fs for the non-adjusted fleets
 if (prj_bycatch_on==NO)
  for (int k=1;k<=nfleet;k++) log_fimpbar(k) = log(1.0e-10);
 else
  for (int k=1;k<=nfleet;k++) log_fimpbar(k) = log(Fave(k));
 // Should Bmsy be simulatation-specific or a pre-specified value
 if (Fixed_prj_Bmsy < 0) Bmsy_out = spr_bmsy; else Bmsy_out = Fixed_prj_Bmsy;
  cout<<"Before projections"<<endl;
 // Do projections
 IsProject = PROJECT;
 if (prj_Nstrat > 0 & prj_replicates > 0)
  for (int isim=1;isim<=prj_replicates;isim++)
   {
	cout<<"SR"<<Stock_rec_prj<<endl;
    // generate future recruitment
    if (Initial_eps < -998) eps1 = randn(rng); else eps1 = Initial_eps;
    for (int iproj=1;iproj<=nproj;iproj++)
     {
      if (Stock_rec_prj==UNIFORMSR)
       {
        index = prj_futRec_syr+(int)floor((float(prj_futRec_nyr)-float(prj_futRec_syr)+1.0)*randu(rng));
        fut_recruits(1,iproj) = recruits(1,index);
        if (nsex==2) fut_recruits(2,iproj) = recruits(2,index);
       }
      if (Stock_rec_prj==RICKER || Stock_rec_prj==BEVHOLT || Stock_rec_prj==MEAN_RECRUIT)
       {
        fut_recruits(1,iproj) = mfexp(eps1*SigmaR_prj-SigmaR_prj*SigmaR_prj/2.0);
        if (iproj != nproj) eps1 = Prow_prj*eps1 + sqrt(1.0-square(Prow_prj))*randn(rng);
        if (nsex==2) fut_recruits(2,iproj) = fut_recruits(1,iproj);
       }
     }
	 cout<<"SRdone"<<endl;
    for (int irun=1;irun<=prj_Nstrat;irun++)
     {
      // Set F
      Fmult = 1.e-10 + prj_lowF + float(irun-1)*(prj_hiF-prj_lowF)/float(prj_Nstrat-1);
      for (int k=1;k<=nfleet;k++)
       if (Ffixed(k) != 1) log_fimpbar(k) = log(Fmult);
      cout<<"Projectbio"<<endl;
      Bproj = project_biomass(nyr, nproj);
      mcoutPROJ << NfunCall << " " << isim << " " << irun << " " << exp(log_fimpbar) << " " << Bmsy_out << " ";
      for (int i=nyr+1;i<=nyr+nproj;i++) mcoutPROJ <<  Bproj(i) << " ";
      cout << Bproj(nyr+nproj-1) << endl;
      mcoutPROJ <<endl;
     }
   }
   cout<<"over projections"<<endl;
 if (NfunCall == max_prj) exit(1);
}

void model_parameters::calc_sdreport(void)
{
  dvar4_array ftmp(1,nsex,syr,nyr,1,nseason,1,nclass);           ///> Fishing mortality
  dvar4_array ftmp2(1,nsex,syr,nyr,1,nseason,1,nclass);          ///> Fishing mortality
  // save the fishing mortality rates
  ftmp = F;  ftmp2 = F2;
  // standard deviations of assessment outcomes
  sd_log_recruits = log(recruits);
  sd_log_ssb = log(calc_ssb());
  //Added 13 lines by Jie
  sd_last_ssb = spr_depl * Bmsy;
 // for (int i=syr; i<= nyr-6; i++)
 // // for (int i=syr+1; i<= nyr; i++)
 // {
 //   sdrRec(i) = recruits(1,i+6)+recruits(2,i+6);            //These are for spawning per recruits
 //   sdrLnRec(i) = log(sdrRec(i));
 //   sdrMMB(i) = mfexp(sd_log_ssb(i));
 //   sdrLnRecMMB(i) = log(sdrRec(i)/sdrMMB(i));
   // sdrRec(i) = recruits(1,i)+recruits(2,i);         //These are for recruits
   // sdrLnRec(i) = log(sdrRec(i));
   // sdrMMB(i) = mfexp(sd_log_ssb(i));
   // sdrLnRecMMB(i) = log(sdrRec(i));
  //}
  for ( int i = syr; i <= nyr-1; i++ )  sd_fbar(i) = mean(F(1,i));
  // projection outcomes
  sd_rbar = spr_rbar;
  sd_ssbF0 = ssbF0;
  sd_Bmsy = Bmsy;
  sd_depl = spr_depl;
  sd_ofl = spr_cofl;
  // Zero catch
  F.initialize();
  for ( int h = 1; h <= nsex; h++ )
   for ( int i = syr; i <= nyr; i++ )
    for ( int j = 1; j <= nseason; j++ )
     for ( int l = 1; l <= nclass; l++)
      F2(h,i,j,l) = 1.0e-10;
  calc_total_mortality();
  calc_initial_numbers_at_length();
  update_population_numbers_at_length();
  sd_log_dyn_Bzero = log(calc_ssb())(syr+1,nyr);
  sd_log_dyn_Bzero = (sd_log_ssb(syr+1,nyr)) - (sd_log_dyn_Bzero);
  // Actual catch
  F = ftmp;
  F2 = ftmp2;
  calc_total_mortality();
  calc_initial_numbers_at_length();
  update_population_numbers_at_length();
  /**
   * @brief Calculate sdnr and MAR
  **/
}

void model_parameters::get_all_sdnr_MAR()
{
  {
   for ( int k = 1; k <= nSurveys; k++ )
    {
     //dvector stdtmp = cpue_sd(k) * 1.0 / cpue_lambda(k);
     //dvar_vector restmp = elem_div(log(elem_div(obs_cpue(k), pre_cpue(k))), stdtmp) + 0.5 * stdtmp;
     //sdnr_MAR_cpue(k) = calc_sdnr_MAR(value(restmp));
    }
   for ( int k = 1; k <= nSizeComps; k++ )
    {
     sdnr_MAR_lf(k) = calc_sdnr_MAR(value(d3_res_size_comps(k)));
    }
   //Francis_weights = calc_Francis_weights();
  }
  /**
   * @brief find the standard deviation of the standardized residuals and their median
  **/
}

dvector model_parameters::calc_sdnr_MAR(dvector tmpVec)
{
  {
    dvector out(1,2);
    dvector tmp = fabs(tmpVec);
    dvector w = sort(tmp);
    out(1) = std_dev(tmpVec);                 // sdnr
    out(2) = w(floor(0.5*(size_count(w)+1))); // MAR
    return out;
  }
}

dvector model_parameters::calc_sdnr_MAR(dmatrix tmpMat)
{
  {
    dvector tmpVec(1,size_count(tmpMat));
    dvector out(1,2);
    int dmin,dmax;
    dmin = 1;
    for ( int ii = tmpMat.indexmin(); ii <= tmpMat.indexmax(); ii++ )
     {
      dmax = dmin + size_count(tmpMat(ii)) - 1;
      tmpVec(dmin,dmax) = tmpMat(ii).shift(dmin);
      dmin = dmax + 1;
     }
    dvector tmp = fabs(tmpVec);
    dvector w = sort(tmp);
    out(1) = std_dev(tmpVec);                 // sdnr
    out(2) = w(floor(0.5*(size_count(w)+1))); // MAR
    return out;
  }
  /**
   * @brief Calculate Francis weights
   * @details this code based on equation TA1.8 in Francis(2011) should be changed so separate weights if by sex
   *
   * Produces the new weight that should be used.
  **/
}

dvector model_parameters::calc_Francis_weights()
{
  {
   int j,nobs;
   double Obs, Pre, Var;
   dvector lfwt(1,nSizeComps);
   for ( int k = 1; k <= nSizeComps; k++ )
    {
     nobs = nSizeCompRows(k);
     dvector resid(1,nobs);
     j = 1;
     resid.initialize();
     for ( int i = 1; i <= nSizeCompRows(k); i++ )
      {
       cout << k << " " << i << endl;
       cout << d3_obs_size_comps(k,i) << endl;
       cout << d3_pre_size_comps(k,i) << endl;
       cout << mid_points << endl;
       Obs = sum(elem_prod(d3_obs_size_comps(k,i), mid_points));
       cout << Obs << endl;
       Pre = sum(elem_prod(value(d3_pre_size_comps(k,i)), mid_points));
       Var = sum(elem_prod(value(d3_pre_size_comps(k,i)), square(mid_points)));
       Var -= square(Pre);
       resid(j++) = (Obs - Pre) / sqrt(Var * 1.0 / (size_comp_sample_size(k,i) * lf_lambda(k)));
      }
     lfwt(k) = 1.0 / (square(std_dev(resid)) * ((nobs - 1.0) / (nobs * 1.0)));
     lfwt(k) *= lf_lambda(k);
    }
    return lfwt;
   }
  /**
   * @brief calculate effective sample size
   * @details Calculate the effective sample size
   *
   * @param observed proportions
   * @param predicted proportions
  **/
}

void model_parameters::CreateOutput(void)
{
  int Ipar,Jpar,Npar,NparEst;
  int nnnn;                                                          //
  cout << "here" << endl;
  get_all_sdnr_MAR();                                                ///> Output specific to diagnostics
  cout << "here" << endl;
  cout << "+--------------------------+" << endl;
  cout << "| Beginning report section |" << endl;
  cout << "+--------------------------+" << endl;
  OutFile1.close();
  OutFile1.open("Gmacsall.out");
  OutFile2.close();
  OutFile2.open("gmacs.rep");
  OutFile3.close();
  OutFile3.open("personal.rep");
  // Likelihood summary
  OutFile1 << "#Likelihoods_by_type (raw and weighted)" << endl;
  OutFile1 << "Catch data             : " << sum(nloglike(1)) << " " << sum(elem_prod(nloglike(1),catch_emphasis)) << endl;
  OutFile1 << "Index data             : " << sum(nloglike(2)) << " " << sum(elem_prod(nloglike(2),cpue_emphasis)) << endl;
  OutFile1 << "Size data              : " << sum(nloglike(3)) << " " << sum(elem_prod(nloglike(3),lf_emphasis)) << endl;
  OutFile1 << "Stock recruitment      : " << sum(nloglike(4)) << " " << sum(nloglike(4)) << endl;
  OutFile1 << "Tagging data           : " << sum(nloglike(5)) << " " << sum(nloglike(5)) << endl;
  OutFile1 << "Penalties              : " << sum(elem_prod(nlogPenalty,Penalty_emphasis)) << endl;
  OutFile1 << "Priors                 : " << sum(priorDensity) << endl;
  OutFile1 << "Initial size-structure : " << TempSS << endl;
  OutFile1 << "Total                  : " << objfun << endl;
  OutFile1 << endl;
  // Likelihood summary
  OutFile1 << "#Likelihoods_by_type_and_fleet" << endl;
  OutFile1 << "Catches" << endl;
  OutFile1 << "Raw likelihood: " << nloglike(1) << endl;
  OutFile1 << "Emphasis      : " << catch_emphasis << endl;
  OutFile1 << "Net likelihood: " << elem_prod(nloglike(1),catch_emphasis) << endl;
  OutFile1 << "Index" << endl;
  OutFile1 << "Raw likelihood: " << nloglike(2) << endl;
  OutFile1 << "Emphasis      : " << cpue_emphasis << endl;
  OutFile1 << "Net likelihood: " << elem_prod(nloglike(2),cpue_emphasis) << endl;
  OutFile1 << "Size-composition" << endl;
  OutFile1 << "Raw likelihood: " << nloglike(3) << endl;
  OutFile1 << "Emphasis      : " << lf_emphasis << endl;
  OutFile1 << "Net likelihood: " << elem_prod(nloglike(3),lf_emphasis) << endl;
  OutFile1 << "Recruitment penalities" << endl;
  OutFile1 << "Penalities    : " << nloglike(4) << endl;
  OutFile1 << "Growth likelihood" << endl;
  OutFile1 << "Raw likelihood    : " << nloglike(5) << endl;
  OutFile1 << endl;
  OutFile1 << "#Penalties" << endl;
  OutFile1 << "1. Mean Fbar=0 : " << nlogPenalty(1) << " " << Penalty_emphasis(1) << " " << nlogPenalty(1)*Penalty_emphasis(1) << endl;
  OutFile1 << "2. Mean Fdev   : " << nlogPenalty(2) << " " << Penalty_emphasis(2) << " " << nlogPenalty(2)*Penalty_emphasis(2) << endl;
  OutFile1 << "3. Mdevs       : " << nlogPenalty(3) << " " << Penalty_emphasis(3) << " " << nlogPenalty(3)*Penalty_emphasis(3) << endl;
  OutFile1 << "5. Rec_ini     : " << nlogPenalty(5) << " " << Penalty_emphasis(5) << " " << nlogPenalty(5)*Penalty_emphasis(5) << endl;
  OutFile1 << "6. Rec_dev     : " << nlogPenalty(6) << " " << Penalty_emphasis(6) << " " << nlogPenalty(6)*Penalty_emphasis(6) << endl;
  OutFile1 << "7. Sex ratio   : " << nlogPenalty(7) << " " << Penalty_emphasis(7) << " " << nlogPenalty(7)*Penalty_emphasis(7) << endl;
  OutFile1 << "7. Molt prob   : " << nlogPenalty(8) << " " << Penalty_emphasis(8) << " " << nlogPenalty(8)*Penalty_emphasis(8) << endl;
  OutFile1 << "7. Smooth select   : " << nlogPenalty(9) << " " << Penalty_emphasis(9) << " " << nlogPenalty(9)*Penalty_emphasis(9) << endl;
  OutFile1 << endl;
  // Estimated parameters
  // ====================
  OutFile1 << "#Parameter_count Parameter_type Index Estimate Phase Lower_bound Upper_bound Penalty Standard_error Estimated_parameter_count" << endl;
  Npar = 0; NparEst = 0;
  for (Ipar=1;Ipar<=ntheta;Ipar++)
   {
    Npar +=1;
    OutFile1 << Npar << " : Theta " << Ipar << " : " << theta(Ipar) << " " << theta_phz(Ipar) << " ";
    if (theta_phz(Ipar) > 0 & theta_phz(Ipar) <= current_phase()) { NparEst +=1; CheckBounds(theta(Ipar),theta_lb(Ipar),theta_ub(Ipar));  OutFile1 << priorDensity(NparEst) << " " << ParsOut.sd(NparEst) << " " << NparEst; }
    OutFile1 << endl;
   }
  for (Ipar=1;Ipar<=nGrwth;Ipar++)
   {
    Npar +=1;
    OutFile1 << Npar << " : Growth " << Ipar << " : " << Grwth(Ipar) << " " << Grwth_phz(Ipar) << " ";
    if (Grwth_phz(Ipar) > 0 & Grwth_phz(Ipar) <= current_phase()) { NparEst +=1; CheckBounds(Grwth(Ipar),Grwth_lb(Ipar),Grwth_ub(Ipar));  OutFile1 << priorDensity(NparEst) << " " << ParsOut.sd(NparEst) << " " << NparEst; }
    OutFile1 << endl;
   }
  for (Ipar=1;Ipar<=nslx_pars;Ipar++)
   {
    Npar +=1;
    OutFile1 << Npar << " : nslx_pars " << Ipar << " : " << log_slx_pars(Ipar) << " " << slx_phzm(Ipar) << " ";
    if (slx_phzm(Ipar) > 0 & slx_phzm(Ipar) <= current_phase()) { NparEst +=1; CheckBounds(log_slx_pars(Ipar),slx_lb(Ipar),slx_ub(Ipar));  OutFile1 << priorDensity(NparEst) << " " << ParsOut.sd(NparEst) << " " << NparEst; }
    OutFile1 << endl;
   }
  for (Ipar=1;Ipar<=NumAsympRet;Ipar++)
   {
    Npar +=1;
    OutFile1 << Npar << " : NumAsympRet " << Ipar << " : " << Asymret(Ipar) << " " << AsympSel_phz(Ipar) << " ";
    if (AsympSel_phz(Ipar) > 0 & AsympSel_phz(Ipar) <= current_phase()) { NparEst +=1; CheckBounds(Asymret(Ipar),AsympSel_lb(Ipar),AsympSel_ub(Ipar));  OutFile1 << priorDensity(NparEst) << " " << ParsOut.sd(NparEst) << " " << NparEst; }
    OutFile1 << endl;
   }
  for (Ipar=1;Ipar<=nfleet;Ipar++)
   {
    Npar +=1;
    OutFile1 << Npar << " : log_fbar " << Ipar << " : " << log_fbar(Ipar) << " " << f_phz(Ipar) << " ";
    if (f_phz(Ipar) > 0 & f_phz(Ipar) <= current_phase()) { NparEst +=1; CheckBounds(log_fbar(Ipar),-1000.0,1000.0);  OutFile1 << priorDensity(NparEst) << " " << ParsOut.sd(NparEst) << " " << NparEst; }
    OutFile1 << endl;
   }
  for (Ipar=1;Ipar<=nfleet;Ipar++)
   for (Jpar=1;Jpar<=nFparams(Ipar);Jpar++)
    {
     Npar +=1;
     OutFile1 << Npar << " : log_fdev " << Ipar << " : " << log_fdev(Ipar,Jpar) << " " << f_phz(Ipar) << " ";
     if (f_phz(Ipar) > 0 & f_phz(Ipar) <= current_phase()) { NparEst +=1; CheckBounds(log_fdev(Ipar,Jpar),-1000.0,1000.0);  OutFile1 << priorDensity(NparEst) << " " << ParsOut.sd(NparEst) << " " << NparEst; }
     OutFile1 << endl;
    }
  for (Ipar=1;Ipar<=nfleet;Ipar++)
   {
    Npar +=1;
    OutFile1 << Npar << " : log_foff " << Ipar << " : " << log_foff(Ipar) << " " << foff_phz(Ipar) << " ";
    if (foff_phz(Ipar) > 0 & foff_phz(Ipar) <= current_phase()) { NparEst +=1; CheckBounds(log_foff(Ipar),-1000.0,1000.0);  OutFile1 << priorDensity(NparEst) << " "<< ParsOut.sd(NparEst) << " " << NparEst; }
    OutFile1 << endl;
   }
  for (Ipar=1;Ipar<=nfleet;Ipar++)
   for (Jpar=1;Jpar<=nYparams(Ipar);Jpar++)
    {
     Npar +=1;
     OutFile1 << Npar << " : log_fdov " << Ipar << " : " << log_fdov(Ipar,Jpar) << " " << foff_phz(Ipar) << " ";
     if (foff_phz(Ipar) > 0 & foff_phz(Ipar) <= current_phase()) { NparEst +=1; CheckBounds(log_fdov(Ipar,Jpar),-1000.0,1000.0);  OutFile1 << priorDensity(NparEst) << " " << ParsOut.sd(NparEst) << " " << NparEst; }
     OutFile1 << endl;
    }
  for (Ipar=1;Ipar<=nclass;Ipar++)
   {
    Npar +=1;
    OutFile1 << Npar << " : rec_ini " << Ipar << " : " << rec_ini(Ipar) << " " << rec_ini_phz << " ";
    if (rec_ini_phz > 0 & rdv_phz <= current_phase()) { NparEst +=1; CheckBounds(rec_ini(Ipar),-14.0,14.0);  OutFile1 << priorDensity(NparEst) << " " << ParsOut.sd(NparEst) << " " << NparEst; }
    OutFile1 << endl;
   }
  for (Ipar=rdv_syr;Ipar<=rdv_eyr;Ipar++)
   {
    Npar +=1;
    OutFile1 << Npar << " : rec_dev_est " << Ipar << " : " << rec_dev_est(Ipar) << " " << rdv_phz << " ";
    if (rdv_phz > 0 & rdv_phz <= current_phase()) { NparEst +=1; CheckBounds(rec_dev_est(Ipar),-8.0,8.0);  OutFile1 << priorDensity(NparEst) << " " << ParsOut.sd(NparEst) << " " << NparEst; }
    OutFile1 << endl;
   }
  for (Ipar=rdv_syr;Ipar<=rdv_eyr;Ipar++)
   {
    Npar +=1;
    OutFile1 << Npar << " : logit_rec_prop_est " << Ipar << " : " << logit_rec_prop_est(Ipar) << " " << rec_prop_phz << " ";
    if (rec_prop_phz > 0 & rec_prop_phz <= current_phase()) { NparEst +=1; CheckBounds(logit_rec_prop_est(Ipar),-100.0,100.0);  OutFile1 << priorDensity(NparEst) << " " << ParsOut.sd(NparEst) << " " << NparEst; }
    OutFile1 << endl;
   }
  for (Ipar=1;Ipar<=nMdev;Ipar++)
   {
    Npar +=1;
    OutFile1 << Npar << " : m_dev_est " << Ipar << " : " << m_dev_est(Ipar) << " " << Mdev_phz(Ipar) << " ";
    if (Mdev_phz(Ipar) > 0 & Mdev_phz(Ipar) <= current_phase()) { NparEst +=1; CheckBounds(m_dev_est(Ipar),Mdev_lb(Ipar),Mdev_ub(Ipar));  OutFile1 << priorDensity(NparEst) << " " << ParsOut.sd(NparEst) << " " << NparEst; }
    OutFile1 << endl;
   }
  for (Ipar=1;Ipar<=nSizeComps;Ipar++)
   {
    Npar +=1;
    OutFile1 << Npar << " : log_vn " << Ipar << " : " << log_vn(Ipar) << " " << nvn_phz(Ipar) << " ";
    if (nvn_phz(Ipar) > 0 & nvn_phz(Ipar) <= current_phase()) { NparEst +=1; CheckBounds(log_vn(Ipar),-1000.0,1000.0);  OutFile1 << priorDensity(NparEst) << " " << ParsOut.sd(NparEst) << " " << NparEst; }
    OutFile1 << endl;
   }
  for (Ipar=1;Ipar<=nSurveys;Ipar++)
   {
    Npar +=1;
    OutFile1 << Npar << " : survey_q " << Ipar << " : " << survey_q(Ipar) << " " << q_phz(Ipar) << " ";
    if (q_phz(Ipar) > 0 & q_phz(Ipar) <= current_phase()) { NparEst +=1; CheckBounds(survey_q(Ipar),q_lb(Ipar),q_ub(Ipar));  OutFile1 << priorDensity(NparEst) << " " <<ParsOut.sd(NparEst) << " " << NparEst; }
    OutFile1 << endl;
   }
  for (Ipar=1;Ipar<=nSurveys;Ipar++)
   {
    Npar +=1;
    OutFile1 << Npar << " : log_add_cvt " << Ipar << " : " << log_add_cv(Ipar) << " " << cv_phz(Ipar) << " ";
    if (cv_phz(Ipar) > 0 & cv_phz(Ipar) <= current_phase()) { NparEst +=1; CheckBounds(log_add_cv(Ipar),log_add_cv_lb(Ipar),log_add_cv_ub(Ipar));  OutFile1 << priorDensity(NparEst) << " " <<ParsOut.sd(NparEst) << " " << NparEst; }
    OutFile1 << endl;
   }
  OutFile1 << endl;
  OutFile1 << "#--------------------------------------------------------------------------------------------" << endl;
  REPORT(fleetname)
  //REPORT(name_read_flt);
  //REPORT(name_read_srv);
  REPORT(nfleet);
  REPORT(n_grp);
  REPORT(nsex);
  REPORT(nshell);
  REPORT(nmature);
  REPORT(syr);
  REPORT(nyr);
  REPORT(nseason);
  REPORT(isex);
  REPORT(imature);
  REPORT(ishell);
  dvector mod_yrs(syr,nyrRetro);
  mod_yrs.fill_seqadd(syr,1);
  REPORT(mod_yrs);
  REPORT(mid_points);
  REPORT(mean_wt);
  REPORT(maturity);
  OutFile1 << endl;
  OutFile1 << "#--------------------------------------------------------------------------------------------" << endl;
  OutFile1 << "Simple likelihood" << endl;
  REPORT(nloglike);
  REPORT(nlogPenalty);
  REPORT(priorDensity);
  OutFile1 << endl;
  // catches
  OutFile1 << "#--------------------------------------------------------------------------------------------" << endl;
  OutFile1 << "Catch_data_summary" << endl;
  calc_predicted_catch_out();
  REPORT(dCatchData);
  REPORT(obs_catch);
  REPORT(obs_effort);
  REPORT(pre_catch);
  REPORT(res_catch);
  REPORT(log_q_catch);
  REPORT(obs_catch_out);
  REPORT(obs_catch_effort);
  REPORT(pre_catch_out);
  REPORT(res_catch_out);
  REPORT(dCatchData_out);
  OutFile1 << endl;
  // index data
  OutFile1 << "#--------------------------------------------------------------------------------------------" << endl;
  OutFile1 << "Index_data_summary" << endl;
  REPORT(dSurveyData);
  for ( int k = 1; k <= nSurveys; k++ )
   if ( cpue_lambda(k) != 1.0 )
    cpue_cv_add(k) = sqrt(exp(square(cpue_sd(k) * 1.0 / cpue_lambda(k))) - 1.0);
   else
    cpue_cv_add(k) = cpue_cv(k) + value(mfexp(log_add_cv(k)));
  REPORT(cpue_cv_add);
  REPORT(obs_cpue);
  REPORT(pre_cpue);
  REPORT(res_cpue);
  REPORT(survey_q);
  OutFile1 << "CPUE: standard deviation and median" << endl;
  REPORT(sdnr_MAR_cpue);
  OutFile1 << endl;
  // index data
  OutFile1 << "#--------------------------------------------------------------------------------------------" << endl;
  OutFile1 << "Size_data_summary" << endl;
  OutFile1 << "Year, Seas, Fleet,  Sex,  Type, Shell,  Maturity, Nsamp,  DataVec (obs), DataVec (pred)" << endl;
  int oldk = 0;
  for (int ii=1; ii<=nSizeComps_in;ii++)
   {
    int k = iCompAggregator(ii);
    if ( oldk != k )
     for (int jj=1;jj<=nSizeCompRows_in(ii);jj++)
      if (d3_SizeComps_in(ii,jj,-7) <= nyrRetro || (d3_SizeComps_in(ii,jj,-7) == nyrRetro+1 & d3_SizeComps_in(ii,jj,-6) == 1) )
       {
        for (int kk=-7;kk<=1;kk++) OutFile1 << int(d3_SizeComps_in(ii,jj,kk)) << " ";
        OutFile1 << size_comp_sample_size(k,jj) << "   ";
        OutFile1 << d3_obs_size_comps(k,jj) << "   ";
        OutFile1 << d3_pre_size_comps(k,jj) << endl;
       }
      oldk = k;
    }
  for ( int kk = 1; kk <= nSizeComps_in; kk++ )
   for ( int ii = 1; ii <= nSizeCompRows_in(kk); ii++ )
    {
     d3_obs_size_comps_out(kk,ii) = d3_obs_size_comps_in(kk,ii) / sum(d3_obs_size_comps_in(kk,ii));                             
     d3_pre_size_comps_out(kk,ii) = d3_pre_size_comps_in(kk,ii) / sum(d3_pre_size_comps_in(kk,ii));                            
     d3_res_size_comps_out(kk,ii) = d3_obs_size_comps_out(kk,ii) - d3_pre_size_comps_out(kk,ii); // WRONG, DARCY 29 jULY 2016  
    }
  REPORT(d3_SizeComps_in);
  REPORT(d3_obs_size_comps_out);              //changed by Jie: output the size comps used to compute likelihood: total 27 lines below:
  REPORT(d3_pre_size_comps_out);              
  REPORT(d3_res_size_comps_out);              
  if (nSizeComps != nSizeComps_in)              
   nnnn = nSizeComps;                           
  else                                          
   nnnn = nSizeComps_in;                        
  for ( int kk = 1; kk <= nnnn; kk++ )          
   {
    OutFile1<<"d3_obs_size_comps_"<<kk<<endl;
    OutFile1<<d3_obs_size_comps(kk)<<endl;  
    OutFile2<<"d3_obs_size_comps_"<<kk<<endl;
    OutFile2<<d3_obs_size_comps(kk)<<endl; 
	} 
  for ( int kk = 1; kk <= nnnn; kk++ )          
   {
    OutFile1<<"d3_pre_size_comps_"<<kk<<endl;
    OutFile1<<d3_pre_size_comps(kk)<<endl;  
    OutFile2<<"d3_pre_size_comps_"<<kk<<endl;
    OutFile2<<d3_pre_size_comps(kk)<<endl;  
	} 
  for ( int kk = 1; kk <= nnnn; kk++ )          
   {
    OutFile1<<"d3_res_size_comps_"<<kk<<endl;
    OutFile1<<d3_res_size_comps(kk)<<endl;  
    OutFile2<<"d3_res_size_comps_"<<kk<<endl;
    OutFile2<<d3_res_size_comps(kk)<<endl;                                     
   }    
  for ( int ii = 1; ii <= nSizeComps; ii++ )
   {
    // Set final sample-size for composition data for comparisons
    size_comp_sample_size(ii) = value(mfexp(log_vn(ii))) * size_comp_sample_size(ii);
   }
  REPORT(size_comp_sample_size);
  OutFile1 << "Size data: standard deviation and median" << endl;
  REPORT(sdnr_MAR_lf);
  //REPORT(Francis_weights);
  OutFile1 << endl;
  // Selectivity-related outouts
  OutFile1 << "#--------------------------------------------------------------------------------------------" << endl;
  OutFile1 << "Selectivity" << endl;
  OutFile1 << "#slx_capture" << endl;
  OutFile1 << "#Year Sex Fleet Selectivity" << endl;
  for ( int i = syr; i <= nyrRetro; i++ ) for ( int h = 1; h <= nsex; h++ ) for ( int j = 1; j <= nfleet; j++ )
    OutFile1 << i << " " << h << " " << j << " " << mfexp(log_slx_capture(j,h,i)) << endl;
  OutFile1 << "#slx_retaind" << endl;
  OutFile1 << "#Year Sex Fleet Retention" << endl;
  for ( int i = syr; i <= nyrRetro; i++ ) for ( int h = 1; h <= nsex; h++ ) for ( int j = 1; j <= nfleet; j++ )
    OutFile1 << i << " " << h << " " << j << " " << mfexp(log_slx_retaind(j,h,i)) << endl;
  OutFile1 << "#slx_discard" << endl;
  OutFile1 << "#Year Sex Fleet Discard" << endl;
  for ( int i = syr; i <= nyrRetro; i++ ) for ( int h = 1; h <= nsex; h++ ) for ( int j = 1; j <= nfleet; j++ )
    OutFile1 << i << " " << h << " " << j << " " << mfexp(log_slx_discard(j,h,i)) << endl;
  OutFile1 << endl;
  REPORT(slx_control_in);
  REPORT(slx_control);
  OutFile1 << endl;
  OutFile2 << "slx_capture" << endl;
  for ( int i = syr; i <= nyr; i++ ) for ( int h = 1; h <= nsex; h++ ) for ( int j = 1; j <= nfleet; j++ )
    OutFile2 << i << " " << h << " " << j << " " << mfexp(log_slx_capture(j,h,i)) << endl;
  OutFile2 << "slx_retaind" << endl;
  for ( int i = syr; i <= nyr; i++ ) for ( int h = 1; h <= nsex; h++ ) for ( int j = 1; j <= nfleet; j++ )
    OutFile2 << i << " " << h << " " << j << " " << mfexp(log_slx_retaind(j,h,i)) << endl;
  OutFile2 << "slx_discard" << endl;
  for ( int i = syr; i <= nyr; i++ ) for ( int h = 1; h <= nsex; h++ ) for ( int j = 1; j <= nfleet; j++ )
    OutFile2 << i << " " << h << " " << j << " " << mfexp(log_slx_discard(j,h,i)) << endl;
  OutFile2 << endl;
  OutFile1 << "#--------------------------------------------------------------------------------------------" << endl;
  OutFile1 << "#Natural, Fishing and Total mortality" << endl;
  REPORT(m_prop);
  OutFile1 << "#Natural_mortality" << endl;
  REPORT(M);
  REPORT(xi);
  REPORT(log_fbar);
  REPORT(ft);
  REPORT(F);
  OutFile1 << endl;
  OutFile2 << "selectivity" << endl; 
  for ( int h = 1; h <= nsex; h++ ) for ( int j = 1; j <= nfleet; j++ )
    OutFile2 << syr << " " << h << " " << j << " " << mfexp(log_slx_capture(j,h,syr)) << endl; 
  for ( int h = 1; h <= nsex; h++ ) for ( int j = 1; j <= nfleet; j++ )
    OutFile2 << nyr << " " << h << " " << j << " " << mfexp(log_slx_capture(j,h,nyr)) << endl; 
  OutFile2 << "retained" << endl; 
  OutFile2 << syr << " " << "1" << " " << "1" << " " << mfexp(log_slx_retaind(1,1,syr)) << endl;  
  OutFile2 << nyr << " " << "1" << " " << "1" << " " << mfexp(log_slx_retaind(1,1,nyr)) << endl;               
  OutFile1 << "#Fully-selected_fishing mortality by fleet" << endl;
  OutFile1 << "# Sex Year Season Fleet" << endl;
  for (int h=1;h<=nsex;h++)
   for (int i=syr;i<=nyrRetro;i++)
    for (int j=1;j<=nseason;j++)
     {
      OutFile1 << h << " " << i << " " << j << " ";
       for (int k=1;k<=nfleet;k++) OutFile1 << ft(k,h,i,j) << " ";
      OutFile1 << endl;
     }
  OutFile1 << "#Fishing mortality by size-class (continuous)" << endl;
  OutFile1 << "# Sex Year Season Fishing_mortality" << endl;
  for (int h=1;h<=nsex;h++)
   for (int i=syr;i<=nyrRetro;i++)
    for (int j=1;j<=nseason;j++)
     OutFile1 << h << " " << i << " " << j << " " << F(h,i,j) << endl;
  OutFile1 << "#Fishing mortality by size-class (discrete)" << endl;
  OutFile1 << "# Sex Year Season Fishing_mortality" << endl;
  for (int h=1;h<=nsex;h++)
   for (int i=syr;i<=nyrRetro;i++)
    for (int j=1;j<=nseason;j++)
     OutFile1 << h << " " << i << " " << j << " " << F2(h,i,j) << endl;
  OutFile1 << endl;
  OutFile1 << "#Total mortality by size-class (continuous)" << endl;
  OutFile1 << "# Sex Year Season Total_mortality" << endl;
  for (int h=1;h<=nsex;h++)
   for(int m=1;m<=nmature;m++)
    for (int i=syr;i<=nyrRetro;i++)
     for (int j=1;j<=nseason;j++)
      OutFile1 << h << " " << m << " " << i << " " << j << " " << Z(h,m,i,j) << endl;
  OutFile1 << "#Total mortality by size-class (discrete)" << endl;
  OutFile1 << "# Sex Year Season Total_mortality" << endl;
  for (int h=1;h<=nsex;h++)
   for( int m=1;m<=nmature;m++)
	for (int i=syr;i<=nyrRetro;i++)
     for (int j=1;j<=nseason;j++)
      OutFile1 << h << " " << m << " " << i << " " << j << " " << Z2(h,m,i,j) << endl;
  OutFile1 << endl;
  OutFile1 << "#--------------------------------------------------------------------------------------------" << endl;
  OutFile1 << "Recruitment" << endl;
  REPORT(rec_sdd);
  REPORT(rec_ini);
  REPORT(rec_dev);
  REPORT(logit_rec_prop);
  REPORT(recruits);
  OutFile1 << endl;
  OutFile1 << "#--------------------------------------------------------------------------------------------" << endl;
  OutFile1 << "SSB and N" << endl;
  dvector ssb = value(calc_ssb());
  cout << "SSB" << endl;
  cout << ssb << endl;
  REPORT(ssb);
  // Print total numbers at length
  dvar_matrix N_initial(1,n_grp,1,nclass);
  dvar_matrix N_total(syr,nyrRetro+1,1,nclass);
  dvar_matrix N_males(syr,nyrRetro+1,1,nclass);
  dvar_matrix N_females(syr,nyrRetro+1,1,nclass);
  dvar_matrix N_males_new(syr,nyrRetro+1,1,nclass);
  dvar_matrix N_females_new(syr,nyrRetro+1,1,nclass);
  dvar_matrix N_males_old(syr,nyrRetro+1,1,nclass);
  dvar_matrix N_females_old(syr,nyrRetro+1,1,nclass);
  dvar_matrix N_males_mature(syr,nyrRetro+1,1,nclass);
  dvar_matrix N_females_mature(syr,nyrRetro+1,1,nclass);
  N_total.initialize();
  N_males.initialize();
  N_females.initialize();
  N_males_new.initialize();
  N_females_new.initialize();
  N_males_old.initialize();
  N_females_old.initialize();
  N_males_mature.initialize();
  N_females_mature.initialize();
  for ( int i = syr; i <= nyrRetro+1; i++ )
   for ( int l = 1; l <= nclass; l++ )
    for ( int k = 1; k <= n_grp; k++ )
     {
      if ( isex(k) == 1 )
       {
        N_males(i,l) += d4_N(k,i,season_N,l);
        if ( ishell(k) == 1 )
         N_males_new(i,l) += d4_N(k,i,season_N,l);
        if ( ishell(k) == 2 )
         N_males_old(i,l) += d4_N(k,i,season_N,l);
        if ( imature(k) == 1 )
         N_males_mature(i,l) += d4_N(k,i,season_N,l);
       }
      else
       {
        N_females(i,l) += d4_N(k,i,season_N,l);
        if ( ishell(k) == 1 )
         N_females_new(i,l) += d4_N(k,i,season_N,l);
        if ( ishell(k) == 2 )
         N_females_old(i,l) += d4_N(k,i,season_N,l);
        if ( imature(k) == 1 )
         N_females_mature(i,l) += d4_N(k,i,season_N,l);
       }
      N_total(i,l) += d4_N(k,i,season_N,l);
     }
  for ( int k = 1; k <= n_grp; k++ )  N_initial(k) = d4_N(k)(syr)(1);
  REPORT(N_initial);
  REPORT(N_total);
  REPORT(N_males);
  if (nsex > 1) REPORT(N_females);
  REPORT(N_males_new);
  if (nsex > 1) REPORT(N_females_new);
  REPORT(N_males_old);
  if (nsex > 1) REPORT(N_females_old);
  REPORT(N_males_mature);
  if (nsex > 1) REPORT(N_females_mature);
  OutFile1 << endl;
  OutFile1 << "#--------------------------------------------------------------------------------------------" << endl;
  OutFile1 << "#Molting and growth" << endl;
  REPORT(molt_increment);
  REPORT(dPreMoltSize);
  REPORT(iMoltIncSex);
  REPORT(dMoltInc);
  // Molting probability
  REPORT(molt_probability);                                                           ///> vector of molt probabilities
  OutFile1 << "growth_transition" << endl;
  for (int h=1; h <= nsex; h++)
   for (int i=1;i<=nSizeIncVaries(h);i++)
    {
     OutFile1 << "#growth_matrix for (sex, increment_no) " << h << " " << i << endl;
     OutFile1 << trans(growth_transition(h,i)) << endl;
	 OutFile2 << "growth_matrix_" << h << "_" << i << endl;
     OutFile2 << trans(growth_transition(h,i)) << endl;
    }
  // Special output 
  if (verbose>3) cout<<"writing MyOutput"<<endl;
  MyOutput();
  if (verbose>3) cout<<"Finished MyOutput"<<endl;
  // Projection stuff
  if ( last_phase() )
   {
	cout<<"last phase"<<endl;
    OutFile1 << endl;
    OutFile1 << "#--------------------------------------------------------------------------------------------" << endl;
    OutFile1 << "#Reference points" << endl;
    // calculate the reference points
    calc_spr_reference_points2(1);
    OutFile1 << "#----------------------------" << endl;
    OutFile1 << "#- Reference points and OFL -" << endl;
    OutFile1 << "#----------------------------" << endl;
    REPORT(spr_syr);
    REPORT(spr_nyr);
    REPORT(spr_rbar);
    REPORT(spr_sexr);
    REPORT(ssbF0);
    REPORT(spr_bmsy);
    REPORT(spr_depl);
    OutFile1 << "SR_alpha_prj" << endl;;
    OutFile1 << setw(15) << setprecision(8) << setfixed() << SR_alpha_prj << endl;;
    OutFile1 << "SR_beta_prj" << endl;
    OutFile1 << setw(15) << setprecision(8) << setfixed() <<  SR_beta_prj << endl;
    REPORT(spr_fofl);
    REPORT(sd_fmsy);
    REPORT(sd_fofl);
    REPORT(spr_cofl);
    if (Compute_yield_prj==1) REPORT(spr_yield);
   }
  //================================================
  //==Report likelihood to .REP file  
    // Likelihood summary
  OutFile2 << "Catches_like" << endl;
  OutFile2 <<  elem_prod(nloglike(1),catch_emphasis) << endl;
  OutFile2 << "Index_like" << endl;
  OutFile2 << elem_prod(nloglike(2),cpue_emphasis) << endl;
  OutFile2 << "Size_comp_like" << endl;
  OutFile2 << elem_prod(nloglike(3),lf_emphasis) << endl;
  OutFile2 << "Recruit_pen" << endl;
  OutFile2 <<  nloglike(4) << endl;
  OutFile2 << "Growth_like" << endl;
  OutFile2 <<  nloglike(5) << endl;
  OutFile2 << "MeanF_pen " << endl;
  OutFile2 << nlogPenalty(1)*Penalty_emphasis(1) << endl;
  OutFile2 << "MeanF_dev"  <<endl;
  OutFile2 << nlogPenalty(2)*Penalty_emphasis(2) << endl;
  OutFile2 << "M_devs " <<endl;
  OutFile2 << nlogPenalty(3)*Penalty_emphasis(3) << endl;
  OutFile2 << "Rec_ini" <<endl;
  OutFile2 << nlogPenalty(5)*Penalty_emphasis(5) << endl;
  OutFile2 << "Rec_dev" << endl;
  OutFile2 << nlogPenalty(6)*Penalty_emphasis(6) << endl;
  OutFile2 << "Sex_ratio" << endl;
  OutFile2 << nlogPenalty(7)*Penalty_emphasis(7) << endl;
  OutFile2 << "Molt_prob_smooth" <<endl;
  OutFile2 << nlogPenalty(8)*Penalty_emphasis(8) << endl;
  OutFile2 << "Free_sel_smooth" <<endl;
  OutFile2 << nlogPenalty(9)*Penalty_emphasis(9) << endl;
  OutFile2 << endl;
}

void model_parameters::report(const dvector& gradients)
{
 adstring ad_tmp=initial_params::get_reportfile_name();
  ofstream report((char*)(adprogram_name + ad_tmp));
  if (!report)
  {
    cerr << "error trying to open report file"  << adprogram_name << ".rep";
    return;
  }
  cout << "+--------------------------+" << endl;
  cout << "| Beginning report section |" << endl;
  cout << "+--------------------------+" << endl;
  CreateOutput();
  cout<<"Made output"<<endl;
  save_gradients(gradients);
  cout<<"Finished REPORT_SECTION"<<endl;
}

void model_parameters::set_runtime(void)
{
  dvector temp1("{2000,   800,   1500,  25000, 25000}");
  maximum_function_evaluations.allocate(temp1.indexmin(),temp1.indexmax());
  maximum_function_evaluations=temp1;
  dvector temp("{1.e-2, 1.e-2, 1.e-3, 1.e-3, 1.e-3}");
  convergence_criteria.allocate(temp.indexmin(),temp.indexmax());
  convergence_criteria=temp;
}

void model_parameters::final_calcs()
{
  cout<<"Starting FINAL_SECTION"<<endl;
  CreateOutput();
  cout<<"Finished CreateOutput"<<endl;
    if (ppSLX) {
        //clean up pointer array--probably unnecessary
        cout<<"deleting ppSLX";
        for (int k=0;k<nslx;k++) delete ppSLX[k];
        delete ppSLX;
        cout<<"Finished deleting ppSLX"<<endl;
    }
  //  Print run time statistics to the screen.
  time(&finish);
  elapsed_time = difftime(finish,start);
  hour = long(elapsed_time)/3600;
  minute = long(elapsed_time)%3600/60;
  second = (long(elapsed_time)%3600)%60;
  cout << endl << endl << "*******************************************" << endl;
  cout << endl << endl << "-------------------------------------------" << endl;
  cout << "--Start time: " << ctime(&start) << endl;
  cout << "--Finish time: " << ctime(&finish) << endl;
  cout << "--Runtime: ";
  cout << hour << " hours, " << minute << " minutes, " << second << " seconds" << endl;
  cout << "--Number of function evaluations: " << NfunCall << endl;
  cout << "*******************************************" << endl;
}

void model_parameters::MyOutput(void)
{
  int nnnn;
  // Likelihood summary. Added by Jie, total 10 lines.
  OutFile3 << "Catches" << endl << elem_prod(nloglike(1),catch_emphasis) << endl;
  OutFile3 << "Index" << endl << elem_prod(nloglike(2),cpue_emphasis) << endl;
  OutFile3 << "Size-compositions" << endl << elem_prod(nloglike(3),lf_emphasis) << endl;
  OutFile3 << "Recruitment_penalities" << endl << nloglike(4) << endl;
  OutFile3 << "Tagging_data" << endl << nloglike(5) << endl;
  OutFile3 << "Initial_size-structure" << endl << TempSS << endl;
  OutFile3 << "Other_penalties" << endl << elem_prod(nlogPenalty,Penalty_emphasis) << endl;
  OutFile3 << "Total" << endl << objfun << endl;
  OutFile3 << endl;
  if (datafile == "BBRKC.dat") //added by Jie: output fishing mortalities, selectivities & retained proportions to report file, total 27 lines
  { 
    dvar_matrix ft_pot(1,nsex,syr,nyrRetro);     
    dvar_matrix ft_trawl(1,nsex,syr,nyrRetro);   
    dvar_matrix ft_tanner(1,nsex,syr,nyrRetro);  
    dvar_matrix ft_fixed(1,nsex,syr,nyrRetro);   
    for (int h=1;h<=nsex;h++)               
     for (int i=syr;i<=nyrRetro;i++)             
      {
        ft_pot(h,i) = ft(1,h,i,3);
        ft_trawl(h,i) = ft(2,h,i,5);
        ft_tanner(h,i) = ft(3,h,i,5);
        ft_fixed(h,i) = ft(4,h,i,5);               
      }
    //REPORT(ft_pot);                         
    //REPORT(ft_trawl);                       
    //REPORT(ft_tanner);                      
    //REPORT(ft_fixed); 
  }      
  OutFile3 << "selectivity" << endl; 
  for ( int h = 1; h <= nsex; h++ ) for ( int j = 1; j <= nfleet; j++ )
    OutFile3 << syr << " " << h << " " << j << " " << mfexp(log_slx_capture(j,h,syr)) << endl; 
  for ( int h = 1; h <= nsex; h++ ) for ( int j = 1; j <= nfleet; j++ )
    OutFile3 << nyrRetro << " " << h << " " << j << " " << mfexp(log_slx_capture(j,h,nyrRetro)) << endl; 
  OutFile3 << "retained" << endl; 
  OutFile3 << syr << " " << "1" << " " << "1" << " " << mfexp(log_slx_retaind(1,1,syr)) << endl;  
  OutFile3 << nyrRetro << " " << "1" << " " << "1" << " " << mfexp(log_slx_retaind(1,1,nyrRetro)) << endl;               
  if (nSizeComps != nSizeComps_in)              
   nnnn = nSizeComps;                           
  else                                          
   nnnn = nSizeComps_in;                        
  for ( int kk = 1; kk <= nnnn; kk++ )          
   {
    OutFile3<<"d3_obs_size_comps_"<<kk<<endl;
    OutFile3<<d3_obs_size_comps(kk)<<endl;                          
   } 
  for ( int kk = 1; kk <= nnnn; kk++ )          
   {
    OutFile3<<"d3_pre_size_comps_"<<kk<<endl;
    OutFile3<<d3_pre_size_comps(kk)<<endl;                                    
   } 
  for ( int kk = 1; kk <= nnnn; kk++ )          
   {
    OutFile3<<"d3_res_size_comps_"<<kk<<endl;
    OutFile3<<d3_res_size_comps(kk)<<endl;                                     
   }    
}

model_data::~model_data()
{}

model_parameters::~model_parameters()
{}

#ifdef _BORLANDC_
  extern unsigned _stklen=10000U;
#endif


#ifdef __ZTC__
  extern unsigned int _stack=10000U;
#endif

  long int arrmblsize=0;

int main(int argc,char * argv[])
{
    ad_set_new_handler();
  ad_exit=&ad_boundf;
  time(&start);
  arrmblsize = 50000000;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(1.e7);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(5.e7);
  gradient_structure::set_MAX_NVAR_OFFSET(5000);
  gradient_structure::set_NUM_DEPENDENT_VARIABLES(5000);
  gradient_structure::set_MAX_DLINKS(150000);
    gradient_structure::set_NO_DERIVATIVES();
#ifdef DEBUG
  #ifndef __SUNPRO_C
std::feclearexcept(FE_ALL_EXCEPT);
  #endif
#endif
    gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
    if (!arrmblsize) arrmblsize=15000000;
    model_parameters mp(arrmblsize,argc,argv);
    mp.iprint=10;
    mp.preliminary_calculations();
    mp.computations(argc,argv);
#ifdef DEBUG
  #ifndef __SUNPRO_C
bool failedtest = false;
if (std::fetestexcept(FE_DIVBYZERO))
  { cerr << "Error: Detected division by zero." << endl; failedtest = true; }
if (std::fetestexcept(FE_INVALID))
  { cerr << "Error: Detected invalid argument." << endl; failedtest = true; }
if (std::fetestexcept(FE_OVERFLOW))
  { cerr << "Error: Detected overflow." << endl; failedtest = true; }
if (std::fetestexcept(FE_UNDERFLOW))
  { cerr << "Error: Detected underflow." << endl; }
if (failedtest) { std::abort(); } 
  #endif
#endif
    return 0;
}

extern "C"  {
  void ad_boundf(int i)
  {
    /* so we can stop here */
    exit(i);
  }
}
