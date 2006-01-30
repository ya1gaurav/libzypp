/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/
/** \file zypp/source/yum/YUMGroupImpl.h
 *
*/
#ifndef ZYPP_SOURCE_YUM_YUMGROUPIMPL_H
#define ZYPP_SOURCE_YUM_YUMGROUPIMPL_H

#include "zypp/source/SourceImpl.h"
#include "zypp/detail/SelectionImplIf.h"
#include "zypp/parser/yum/YUMParserData.h"
#include "zypp/Edition.h"

///////////////////////////////////////////////////////////////////
namespace zypp
{ /////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////
  namespace source
  { /////////////////////////////////////////////////////////////////
    namespace yum
    { //////////////////////////////////////////////////////////////

      ///////////////////////////////////////////////////////////////////
      //
      //        CLASS NAME : YUMGroupImpl
      //
      /** Class representing a message
      */
      class YUMGroupImpl : public detail::SelectionImplIf
      {
      public:
        /** Default ctor */
        YUMGroupImpl(
	  Source_Ref source_r,
	  const zypp::parser::yum::YUMGroupData & parsed
	);
	
	virtual ~YUMGroupImpl();

        /** Other requested groups */
	virtual CapSet optionalReq() const;
	/** Requested packages */
	virtual CapSet defaultReq() const;
	/** */
	virtual const TranslatedText & summary() const;
	/** */
	virtual const TranslatedText & description() const;
	/** */
	virtual Text insnotify() const;
	/** */
	virtual Text delnotify() const;
	/** */
	virtual bool providesSources() const;
	/** */
	virtual Label instSrcLabel() const;
	/** */
	virtual Vendor instSrcVendor() const;
        /** */
        virtual ByteCount size() const;	
        /** */
	virtual Label category() const;
        /** */
	virtual bool visible() const;
        /** */
	virtual Label order() const;

      protected:
// _summary
// _description;
        bool _user_visible;
	CapSet _optional_req;
	CapSet _default_req;
      private:
	Source_Ref _source;
      public:
	Source_Ref source() const;
      };
      ///////////////////////////////////////////////////////////////////
    } // namespace yum
    /////////////////////////////////////////////////////////////////
  } // namespace source
  ///////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
} // namespace zypp
///////////////////////////////////////////////////////////////////
#endif // ZYPP_SOURCE_YUM_YUMGROUPIMPL_H
