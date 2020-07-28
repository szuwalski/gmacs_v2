#require(devtools)
#devtools::install_github("seacode/gmacs", subdir = "/gmr", ref = "develop")
# ploting for model 1 under smbkc18a folder - using gmr and Jim's code 
in_path<-"C:/gmacs/gmr/R/"
library(miceadds)
library(ggplot2)
library(ggridges)
library(dplyr)
library(PBSmodelling)
library(reshape2)
source.all( path=in_path, grepstring="\\.R",  print.source=TRUE, file_sep="__"  )

mod_names <- c("nsrkc")
.MODELDIR = c("./nsrkc/")
.THEME    = theme_bw(base_size = 12, base_family = "") +
  theme(strip.text.x = element_text(margin= margin(1,0,1,0)),
        panel.grid.major = element_blank(), 
        panel.grid.minor = element_blank(),
        panel.border = element_blank(),
        panel.background = element_blank(),
        strip.background = element_rect(color="white",fill="white"))

.OVERLAY  = TRUE
.SEX      = c("Aggregate","Male","Female")
.FLEET    = c("Winter_com","Summer_com","ADFG Trawl")
.TYPE     = c("Retained","Discarded","Total")
.SHELL    = c("New","Old")
.MATURITY = c("Aggregate","Mature","Immature")
.SEAS     = c("1","2","3","4","5","6","7")

fn       <- paste0(.MODELDIR, "gmacs")
M        <- lapply(fn, read_admb) #need .prj file to run gmacs and need .rep file here
names(M) <- mod_names


plot_catch(M)

plot_cpue(M, ShowEstErr = TRUE, "ADFG Trawl", ylab = "Survey biomass")

plot_molt_prob(M)

plot_F(M,in_leg_x=.2,in_leg_y=.9)

plot_growth_inc(M)

plot_selectivity(M)

plot_recruitment(M)

mdf <- .get_sizeComps_df(M)
for(x in 1:length(mdf))
{
png(paste("nsrkc/plots/size_comp_",x,".png",sep=""),height=8,width=8,res=1200,units='in')
plot_size_comps(M,which=x)
dev.off()
}

for(x in 1:length(mdf))
{
  png(paste("nsrkc/plots/size_ridges_",x,".png",sep=""),height=8,width=8,res=1200,units='in')
  plot_size_ridges(M,which=x)
  dev.off()
}
plot_natural_mortality(M, plt_knots = FALSE)

plot_ssb(M)

plot_recruitment_size(M)

plot_growth_transition(M)

plot_size_transition(M)



plot_numbers(M)

