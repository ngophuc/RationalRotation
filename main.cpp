#include "Functions.h"
#include "Rotation2D.h"

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

int main()
{
  std::vector<Z2i::Point> X = readImage("../ball_r5.pgm");
  assert(X.size()!=0);
  std::cout<<"X.size="<<X.size()<<std::endl;
  
  //Rotation2D t(M_PI/2.0);
  //Rotation2D t(24,7,25);
  Rotation2D t(3,4,5);
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
