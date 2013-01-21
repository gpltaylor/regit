/*!
 * \author Frantz Maerten, Garry Taylor
 * frantz.maerten@igeoss.com, http://www.igeoss.com
 * taylorg@southport-college.ac.uk
 * \version 1.0
 * \date October 2004
 */

#ifndef XMLTRAVERSAL
#define XMLTRAVERSAL

#include "common.h"
#include <qdom.h>


class IGSXML XMLTraversal {
public:
  XMLTraversal() ;
  XMLTraversal(const QString&) ;
  XMLTraversal(const QDomDocument&) ;

  // =============================================
  //   Various accessors
  // =============================================

  /*!
   * Check the validity of the XMLTraversal instance
   * @return true if the internal document is valid, false otherwise
   */
  bool is_valid() const ;

  /*!
   * Check if a path exists within the document
   * @return true if the path exists, false otherwise
   */
  bool exists(const QString& path) const ;

  /*!
   * Gives the current path within the XMLTraversal
   * @return the current path
   */
  QString pwd() const ;

  /*!
   * Return the node at the current path of the XMLTraversal
   */
  QDomNode currentNode() const ;

  /*!
   * Return the document making this XMLTraversal
   */
  const QDomDocument& document() const ;

  /*!
   * Convert to string for debugging purpose
   */
  QString dump() const ;


  // =============================================
  //   Various modifiers
  // =============================================

  /*!
   * The the new content of the XMLTraversal
   * @param doc the stringified version of the document
   * @return true if the internal document is valid, false otherwise
   */
  bool setDocument(const QString& doc) ;
  /*!
   * The the new content of the XMLTraversal
   * @param doc the document
   * @return true if the internal document is valid, false otherwise
   */
  bool setDocument(const QDomDocument& doc) ;

  /*!
   * To cd to a specific node.
   * You can use:
   *   - a usual path. If a backslash is present at the beginning of the path,
	 *     it starts from the root. Otherwise, it starts from the
	 *     current path (see pwd()). Examples:
	 * <pre>
	 *   cd("/constants/remote/s11") ;
	 *   cd("../..") ;
	 *   // Jump to the root:
	 *   cd() ;
	 *   cd("../../tools/remote/../halfspace") ;
	 * </pre>
   *   - "..." to do a "cd ../.." (an alias)
   *   - no argument: to return to the root of the XMLTraversal.
   *
   * @return true if successful, false otherwise.
   */
  bool cd(const QString& path = QString()) ;

  /*!
   * Create a new directory (a new node). 
   * The tail of the path is the name of the new node, and the remaining
   * path have to be a valid path. You can only create one directory at a time.
   * @return the created element. The return element is invalid (isNull()) if
   * the operation failed.
   */
  QDomElement mkdir(const QString& path) ;

  /*!
   * Remove an existing directory (a node)
   * @return true if succeed, false otherwise
   */
  bool rmdir(const QString& path) ;

  /*!
   * Move or rename a node. Several possible commands:
   *	 - If newpath does exist, and oldpath is not a child of newpath, 
   *	   it moves oldpath to newpath.
   *	 - If newpath doesn't exist (at least the last child of newpath),
   *	   it renames oldpath to newpath
   *
   *	@param oldpath the node to move or rename
   *	@param newpath the new parent or the new name
   *	@return true if successful, false otherwise
   */
  bool mv(const QString& oldpath, const QString& newpath) ;

  /*!
   * Copy a node into another one.
   *	@param source the node to copy
   *	@param target the parent for the copy node
   *	@return true if successful, false otherwise
   */
  bool cp(const QString& source, const QString& target) ;

  /*
   * Get the value of the current QDomElement
   * method added by: Garry Taylor
   */
  QString currentValue();

  /*
   * Sets the value of the current QDomElement
   * method added by: Garry Taylor
   */
   bool setValue(QString value);

   /*
    * Overload to allow changed to QDomElements::Attribute.value
    * without being in the dir
    * method added by: Garry Taylor
    */
    bool setValue(QString path, QString value);

private:
  QDomNode cd_to_node(const QString& path) ;
  QDomDocument doc_ ;
  QDomNode cur_path_node_ ;

} ;

inline QDomNode XMLTraversal::currentNode() const {return cur_path_node_ ;}
inline const QDomDocument& XMLTraversal::document() const {return doc_ ;}

#endif

