#include "Functions.h"
#include "Rotation2D.h"

#include <stdlib.h>
#include <stdio.h>
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/readers/PGMReader.h"
#include "DGtal/images/ImageSelector.h"

using namespace std;
using namespace DGtal;

std::vector<Z2i::Point> readImage(string filename)
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

int main(int argc, const char **argv) {
  printf("Running command: <input_image> [[a b] c | angle (degree)]\n");
  int a=3, b=4, c=5, d;
  double angle = 0;
  string image_name = "../ball_r5.pgm";
  if(argc>1)
    image_name = argv[1];
  
  if(argc==3) { //Rotation2D a b c
    angle = strtod(argv[2],NULL);

    PythagoreanTriple pt = convertAngle2Pythagore(angle*M_PI/180.0);
    a = std::get<0>(pt);
    b = std::get<1>(pt);
    c = std::get<2>(pt);
  }
  
  if(argc==4) { //Rotation2D a b
    a = atoi(argv[2]);//a
    b = atoi(argv[3]);//b
    d = (a*a+b*b);
    c = int(sqrt(d));
    if(c*c!=d) {
      perror("Invalide parameter!");
      exit(0);
    }
  }
  if(argc==5) { //Rotation2D a b c
    a = atoi(argv[2]);//a
    b = atoi(argv[3]);//b
    c = atoi(argv[4]);//c
    d = (a*a+b*b);
    if(c*c!=d) {
      perror("Invalide parameter!");
      exit(0);
    }
  }
  printf("filename= %s and Pythagorean triple is %d %d %d", image_name, a, b, c);
  
  assert(a*a+b*b==c*c); //pythagore triple
  //Rotation2D t(M_PI/2.0);
  //Rotation2D t(24,7,25);
  Rotation2D t(a,b,c);
  
  std::vector<Z2i::Point> X = readImage(image_name);
  assert(X.size()!=0);
  std::cout<<"X.size="<<X.size()<<std::endl;
  
  Z2i::Point p;
  RationalPoint tp;
  cout<<t<<endl;
  for(size_t it=0; it<X.size(); it++) {
    p = X.at(it);
    tp = t.transform(p);
    cout<<"p="<<p<<" and tp="<<tp<<endl;
  }
  return 1;
}
