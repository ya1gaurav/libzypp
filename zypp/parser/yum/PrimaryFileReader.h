/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/

#ifndef ZYPP_PARSER_YUM_PRIMARYFILEPARSER_H
#define ZYPP_PARSER_YUM_PRIMARYFILEPARSER_H

#include "zypp/base/Function.h"
#include "zypp/base/Logger.h"
#include "zypp/parser/xml/Reader.h"
#include "zypp/data/ResolvableData.h"
#include "zypp/parser/ParserProgress.h"

#undef ZYPP_BASE_LOGGER_LOGGROUP
#define ZYPP_BASE_LOGGER_LOGGROUP "parser"

namespace zypp
{
  namespace parser
  {
    namespace yum
    {

  /**
   * Reads through a primary.xml file and collects package data including
   * dependencies.
   * 
   * After a package is read, a \ref zypp::data::Package object is prepared
   * and \ref _callback is called with this object passed in.
   *
   * The \ref _callback is provided on construction.
   *
   * \code
   * PrimaryFileReader reader(repomd_file, 
   *                          bind(&SomeClass::callbackfunc, &object, _1));
   * \endcode
   */
  class PrimaryFileReader
  {
  public:
    /**
     * Callback definition.
     */
    typedef function<bool(const zypp::data::Package &)> ProcessPackage;

    /**
     * Enumeration of some primary.xml tags.
     */
    enum Tag
    {
      tag_NONE,
      tag_package,
      tag_format
    };

    /**
     * Constructor
     * \param primary_file the primary.xml.gz file you want to read
     * \param function to process \ref _package data.
     * 
     * \see PrimaryFileReader::ProcessPackage
     */
    PrimaryFileReader(const Pathname &primary_file, ProcessPackage callback, ParserProgress::Ptr progress);
  
    /**
     * Callback provided to the XML parser.
     */
    bool consumeNode(zypp::xml::Reader & reader_r);

  private:
    /**
     * Function for processing all <code>format</code> tag subtree nodes.
     */
    bool consumeFormatChildNodes(zypp::xml::Reader & reader_r);

  private:
    /** Used to remember primary.xml tag beeing currently processed. */
    Tag _tag;

    /**
     * Used to remember whether we are expecting an rpm:entry tag
     * e.g. for rpm:requires
     */
    bool _expect_rpm_entry;

    /**
     * Type of dependecy beeing processed.
     */
    Dep _dtype;

    /**
     * Number of packages read so far.
     */
    unsigned _count;

    /**
     * Total number of packages to be read. This information is acquired from
     * the <code>packages</code> attribute of <code>metadata<code> tag.
     */
    unsigned _total_packages;

    /**
     * Pointer to the \ref zypp::data::Package object for storing the package
     * metada
     */
    zypp::data::Package *_package;

    /**
     * Callback for processing package metadata passed in through constructor.
     */
    ProcessPackage _callback;

    /**
     * Progress reporting object.
     */
    ParserProgress::Ptr _progress;
    
    long int _old_progress;
  };


    } // ns zypp
  } // ns parser
} // ns yum

#endif /* ZYPP_PARSER_YUM_PRIMARYFILEPARSER_H */

// vim: set ts=2 sts=2 sw=2 et ai:
