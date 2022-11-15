#include "Functions.h"
#include "Rotation2D.h"
#include "Rotation3D.h"

#include "DGtal/io/Color.h"

#include "CLI11.hpp"

//2D
#include "DGtal/io/readers/PGMReader.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/imagesSetsUtils/SetFromImage.h"
#include "DGtal/io/boards/Board2D.h"

//3D
#include "DGtal/io/readers/VolReader.h"
#include "DGtal/io/Display3D.h"
#include "DGtal/io/viewers/Viewer3D.h"
#ifdef WITH_VISU3D_QGLVIEWER
#include "DGtal/io/DrawWithDisplay3DModifier.h"
#endif


using namespace std;
using namespace DGtal;

std::vector<Z2i::Point> readImage2D(string filename)
{
  std::vector<Z2i::Point> vecPtsTmp;
  typedef ImageSelector<Z2i::Domain, unsigned char >::Type Image;
  Image image = PGMReader<Image>::importPGM( filename );
  for ( Z2i::Domain::ConstIterator it = image.domain().begin(); it != image.domain().end(); ++it )
  {
    unsigned char val =  image (*it);
    if(val==255)
      vecPtsTmp.push_back(*it);
  }
  //Center the points
  Z2i::RealPoint cr = getBaryCenter(vecPtsTmp);
  Z2i::Point p, c(round(cr[0]),round(cr[1]));
  std::vector<Z2i::Point> vecPts;
  for(auto it=vecPtsTmp.begin(); it!=vecPtsTmp.end(); it++) {
    p = (*it) - c;
    vecPts.push_back(p);
  }
  return vecPts;
}

std::vector<Z3i::Point> readImage3D(string filename)
{
  std::vector<Z3i::Point> vecPtsTmp;
  typedef ImageSelector < Z3i::Domain, int>::Type Image;
  Image image = VolReader<Image>::importVol(filename);
  for ( Z3i::Domain::ConstIterator it = image.domain().begin(); it != image.domain().end(); ++it ) {
    Z3i::Point p = (*it);
    if(image(p)>0) {
      vecPtsTmp.push_back(*it);
    }
  }
  //Center the points
  Z3i::RealPoint cr = getBaryCenter(vecPtsTmp);
  Z3i::Point p, c(round(cr[0]),round(cr[1]),round(cr[2]));
  std::vector<Z3i::Point> vecPts;
  for(auto it=vecPtsTmp.begin(); it!=vecPtsTmp.end(); it++) {
    p = (*it) - c;
    vecPts.push_back(p);
  }
  
  return vecPtsTmp;
  
}
int main(int argc, char** argv)
{
  CLI::App app;
  string filename;
  int dim = 2;
  int a=3, b=4, c=5;
  int qa=0, qb=1, qc=0, qd=0;
  double angle=0.0;
  int ax=1, ay=0, az=0;
  
  app.description("Apply 2D/3D rational rotation on a given image.\n Typical use example:\n \t RationalRotation --input <filename> --dim [2 3] --ox 1.0 --oy 1.0 --oz 1 -a 1.2 --ax 1 --ay 1 --az 0 --tx 1 --ty 0 --tz 0 \n Example:\n RationalRotation -d 2 -i ../ball_r5.pgm --pa 3 --pb 4 --pc 5 \n RationalRotation -d 3 -i Al.100.vol --qa 3 --qb 4 --qc 5 --qd 5\n");
    
  app.add_option("-i,--input,1",filename,"Input file.")->required()->check(CLI::ExistingFile);
  app.add_option("-d,--dim",dim,"Dimension: 2 or 3 (default 2)",true);
  auto angle_opt = app.add_option("-a,--angle",angle,"Rotation angle in degrees (default 0)",true);
  
  auto pa_opt = app.add_option("--pa",a,"Pythagorean triplet for 2D rotation (default 3)",true);
  auto pb_opt = app.add_option("--pb",b,"Pythagorean triplet for 2D rotation (default 4)",true);
  auto pc_opt = app.add_option("--pc",c,"Pythagorean triplet for 2D rotation (default 5)",true);
  
  auto ax_opt = app.add_option("--ax",ax,"X component of 3D rotation axis (default 1)",true);
  auto ay_opt = app.add_option("--ay",ay,"Y component of 3D rotation axis (default 0)",true);
  auto az_opt = app.add_option("--az",az,"Z component of 3D rotation axis (default 0)",true);
  
  auto qa_opt = app.add_option("--qa",qa,"Quaternion for 3D rotation (default 0)",true);
  auto qb_opt = app.add_option("--qb",qb,"Quaternion for 3D rotation (default 1)",true);
  auto qc_opt = app.add_option("--qc",qc,"Quaternion for 3D rotation (default 0)",true);
  auto qd_opt = app.add_option("--qd",qd,"Quaternion for 3D rotation (default 0)",true);
  
  app.get_formatter()->column_width(40);
  CLI11_PARSE(app, argc, argv);
  // END parse command line using CLI ----------------------------------------------
  
  if(dim==3) {//3D
    std::cout<<"Intput image="<<filename<<std::endl;
    std::vector<Z3i::Point> X = readImage3D(filename);
    assert(X.size()!=0);
    std::cout<<"X.size="<<X.size()<<std::endl;
    
    Rotation3D rot;
    //Initisation the rotation with an angle and an axis
    if (angle_opt->count() > 0 && ax_opt->count() > 0 && ax_opt->count() > 0 && ax_opt->count() > 0) {
      double rot_angle = angle*M_PI/180.0;
      rot = Rotation3D(rot_angle, ax, ay, az);
      cout<<"angle(input)="<<rot_angle<<"(rad) vs angle(quaterion)="<<rot.getAngle()<<endl;
    }
    //Initisation the rotation with a quaternion
    else if (qa_opt->count() > 0 && qb_opt->count() > 0 && qc_opt->count() > 0 && qd_opt->count() > 0) {
      rot = Rotation3D(qa, qb, qc, qd);
    }
    cout<<rot<<endl;
    return 1;
    //Realisation of the rational rotation
    Z3i::Point p;
    RationalPoint3D tp;
    
    for(size_t it=0; it<X.size(); it++) {
      p = X.at(it);
      tp = rot.transform(p);
      cout<<"p="<<p<<" and tp="<<tp<<endl;
    }
  }
  else {//2D
    std::cout<<"Intput image="<<filename<<std::endl;
    std::vector<Z2i::Point> X = readImage2D(filename);
    assert(X.size()!=0);
    std::cout<<"X.size="<<X.size()<<std::endl;
    
    Rotation2D rot;
    //Initisation the rotation with an angle
    if (angle_opt->count() > 0) {
      double rot_angle = angle*M_PI/180.0;
      rot = Rotation2D(rot_angle);
      cout<<"angle(input)="<<rot_angle<<"(rad) vs angle(pythagore)="<<asin(getRealValue(rot.sin))<<endl;
    }
    //Initisation the rotation with a Pythagorean triplet
    else if (pa_opt->count() > 0 && pb_opt->count() > 0 && pc_opt->count() > 0) {
      assert(a*a+b*b==c*c); //pythagore triplet
      rot = Rotation2D(a, b, c);
    }
    cout<<rot<<endl;
    
    //Realisation of the rational rotation
    Z2i::Point p;
    RationalPoint tp;
    for(size_t it=0; it<X.size(); it++) {
      p = X.at(it);
      tp = rot.transform(p);
      cout<<"p="<<p<<" and tp="<<tp<<endl;
    }
  }
  
  return 1;
}
