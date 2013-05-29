/*
 * NexusParser.h
 *
 *  Created on: Feb 22, 2012
 *      Author: jleigh
 */

#ifndef NEXUSPARSER_H_
#define NEXUSPARSER_H_

#include <fstream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>

#include "GeoTrait.h"
#include "SeqParser.h"
#include "Sequence.h"
#include "Trait.h"
#include "Tree.h"

//class SeqParser;


class NexusParser : public SeqParser {
public:
  NexusParser();
  virtual ~NexusParser();

  virtual Sequence & getSeq(std::istream &, Sequence &);
  virtual void putSeq(std::ostream &, const Sequence &);
  virtual void resetParser();
  const std::vector<Tree *> & treeVector() const;
  const std::vector<Trait *> & traitVector() const;
  const std::vector<GeoTrait *> & geoTraitVector() const;
  bool hasGeoTags() const { return _hasGeoTags; };
  bool hasTraits() const { return _hasTraits; };
  
protected:
  //void fixEquals(string &);
  std::string & fixEquals(std::string &);
  
private:
  typedef enum
  {
    // Blocks that are commented out should be supported
	// Important: add block for auxiliary info about haplotypes?
    NoBlock,
    Data,
    Taxa,
    Characters,
    Trees,
    Assumptions,
    //Codons,
    //Notes,
    Unaligned,
    //Distances,
    //Paup,
    //MrBayes,
    //StSplits,
    //Ha
    Traits,
    GeoTags,
    Network,
    Sets,
    Other
  } BlockType;

  typedef enum
  {
    NoKwd,
    Begin,
    End,
    CharstateLabels,
    ClustLabels,
    ClustLongitude,
    ClustLatitude,
    Dimensions,
    Edges,
    Format,
    Matrix,
    TaxLabels,
    //TraitKW,
    TraitLabels,
    TraitLatitude,
    TraitLongitude,
    Translate,
    TreeKW,
    Unknown,
    Vertices,
    VLabels
  } KeyWord;
  
  typedef struct
  {
    std::string name;
    float latitude;
    float longitude;
    unsigned nsamples;
    unsigned clusterID;
    
  } SeqGeoData;
  
  typedef struct
  {
    std::string font;
    std::string legendFont;
    std::string vColour;
    std::string eColour;
    std::string bgColour;
    std::string eView;
    double vSize;
    std::pair<double,double> lPos;
    std::list<std::string> lColours;
  } GraphicsParams;
  

  typedef std::map<std::string, BlockType, std::less<std::string> > strblockmap;
  typedef std::map<std::string, KeyWord, std::less<std::string> > strkwdmap;

  void initGraphicsParams(GraphicsParams &);
  void setupMaps();
  void parseLine(std::string, Sequence &);
  bool cleanComment(std::string &, bool);


  bool _headerWritten;
  bool _firstLineRead;
  //int _nChar;
  //int _nSeq;
  int _seqReadCount;
  int _taxonCount;
  int _seqWriteCount;
  char _gap;
  char _missing;
  char _missingTrait;
  char _match;
  char _traitSep;
  char _geotagSep;
  bool _respectCase;
  bool _inComment;
  bool _inSeq;
  bool _interleave;
  bool _traitsLabeled;
  bool _geotagsLabeled;
  bool _newTaxa;
  bool _taxLabels;
  int _ntraits;
  int _nclusts;
  unsigned _latCount;
  unsigned _lonCount;
  unsigned _nverts;
  unsigned _nedges;
  bool _hasGeoTags;
  bool _hasTraits;  
  const std::string *_keystr;
  std::string *_treestr;
  
  //CharType _dataType;
  BlockType _currentBlock;
  KeyWord _currentKeyWord;
  //std::set<std::string> _taxa;
  std::map<std::string, int> _taxonIndexMap;
  std::vector<std::string> _taxonVect;
  std::vector<std::string> _seqSeqVect;
  //std::string
  Sequence _topSeq; // for replacing "match" chars
  std::vector<int> _taxSets;
  std::vector<bool> _exSets;
  strblockmap _blockMap;
  strkwdmap _kwdMap;
  std::map<std::string, std::string> _treeTaxMap;
  std::vector<Tree *> _trees;
  std::vector<Trait *> _traits;
  
  // Vectors for trait names and locations reused for GeoTags
  std::vector<std::string> _traitNames;
  std::vector<std::pair<float,float> > _traitLocations;
  std::vector<SeqGeoData> _geoTags;
  std::vector<GeoTrait *> _geoTagTraits;
  
  std::vector<double> _plotRect;
  GraphicsParams _netGraphicsParams;
  std::vector<pair<double,double> > _vertices;
  std::vector<pair<unsigned,unsigned> > _edges;
  std::vector<pair<double,double> > _vLabels;

  //bool _geoDataSaved;
  static int _seqidx;
};

// TODO 
// check whether lower-case font families can be parsed by QFont
#endif /* NEXUSPARSER_H_ */
