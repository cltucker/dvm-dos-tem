#Some packages to install for running the calibrator

##boost 1.55
##Eventually the correct version of boost shoul be a yum or apt-get repo, but for now it needs to be downloaded and compiled

###wget -O boost_1_55_0.tar.gz http://sourceforge.net/projects/boost/files/boost/1.55.0/boost_1_55_0.tar.gz/download
###tar xzvf boost_1_55_0.tar.gz
###cd boost_1_55_0/
###./bootstrap.sh
###./b2 install

##readline-devel

###sudo yum install readline-devel

##jsoncpp-devel

###sudo yum install jsoncpp-devel

##You may also need to add a setup script for environment variables specific to your computer
##setup-env-for-ctucker-Fedora19.sh can be used as an example.


