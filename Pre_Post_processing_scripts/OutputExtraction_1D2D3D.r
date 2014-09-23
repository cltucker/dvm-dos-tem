library(ncdf4)
wd <- "/home/colin_tucker/dvm-dos-tem/DATA/Toolik_Inputs/output/"
# Extract a uni-dimension variable;
outputfile <- "cmtbgc_yly-eq.nc"
csvfile <- "out.csv"
out <- nc_open(paste(wd,outputfile, sep="")) #Location of your nc file;
for (i in 1:out$nvars) print(c('rank',i,'varname',out$var[[i]]$name))
for (i in 1:out$ndims) print(c('rank',i,'dimname',out$dim[[i]]$name))

	dim <- out$dim[[]]$vals	#specify the rank of the dimension of the uni-dimensional variable you wanna extract			
	var <- ncvar_get(out, out$var[[]],start=1,count=out$dim[[]]$len) # specify the rank of the variable and the related dimension you wanna extract;
	file <- data.frame(dim,var) #create the output file
	names(file) <- c(out$dim[[1]]$name,out$var[[5]]$name)	#naming the columns of your output file;

write.csv(file, file=csvfile)	
	
# Extract a two-dimensions variable;

out <- nc_open('') #Location of your nc file;
for (i in 1:out$nvars) print(c('rank',i,'varname',out$var[[]]$name))
for (i in 1:out$ndims) print(c('rank',i,'dimname',out$dim[[i]]$name))

valdim1<- out$dim[[1]]$vals
valdim2<- out$dim[[2]]$vals
file <- data.frame()
for(j in 1:1){
	for(i in 1:out$dim[[j]]$len) #loop on the shortest dimension, e.g. month;
	{
	dim2 <- rep(valdim2[i],out$dim[[j]]$len)
	}
}
	var <- data.frame(ncvar_get(out,out$var[[]],start=c(i,1),count=c(1,out$dim[[1]]$len))) #specify the rank of the variable;
	M <- data.frame(valdim1,dim2,var) #merging the three columns
	names(M) <- c(out$dim[[1]]$name,out$dim[[2]]$name,out$var[[]]$name)	#naming the columns of your  file;
	file <- rbind(file,M)	#merging to the output file
	}
}
write.csv(file, file='')

# Extract a three-dimensions variable;

out <- nc_open('') #Location of your nc file;
for (i in 1:out$nvars) print(c('rank',i,'varname',out$var[[i]]$name))
for (i in 1:out$ndims) print(c('rank',i,'dimname',out$dim[[i]]$name))

valdim1<- out$dim[[1]]$vals
valdim2<- out$dim[[2]]$vals
valdim3<- out$dim[[3]]$vals
file <- data.frame()

for (j in 1:out$dim[[3]]$len) #loop on the shortest dimension, e.g. month;
{
	for (i in 1:out$dim[[2]]$len) #loop on the shortest dimension, e.g. month;
	{
		dim3 <- rep(valdim3[j],out$dim[[1]]$len)
		dim2 <- rep(valdim2[i],out$dim[[1]]$len)
		var <- data.frame(ncvar_get(out,out$var[[]],start=c(j,i,1),count=c(1,1,out$dim[[1]]$len))) #specify the rank of the variable;
		M <- data.frame(valdim1,dim2,dim3,var) #merging the three columns
		names(M) <- c(out$dim[[1]]$name,out$dim[[2]]$name,out$dim[[3]]$name,out$var[[]]$name)	#naming the columns of your  file;
		file <- rbind(file,M)	#merging to the output file
	}
}


write.csv(file, file='')
