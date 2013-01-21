/*!
 * \author Frantz Maerten, Garry Taylor
 * frantz.maerten@igeoss.com, http://www.igeoss.com
 * taylorg@southport-college.ac.uk
 * \version 1.0
 * \date October 2004
 */

#include "xmltraversal.h"
#include <qregexp.h>


XMLTraversal::XMLTraversal() {
  cur_path_node_ = doc_ ;
}

XMLTraversal::XMLTraversal(const QString& s) {
  doc_ = QDomDocument() ;
  doc_.setContent(s) ;
  cur_path_node_ = doc_ ;
}

XMLTraversal::XMLTraversal(const QDomDocument& doc) {
  doc_ = doc ;
  cur_path_node_ = doc_ ;
}

bool XMLTraversal::setDocument(const QString& s) {
  doc_ = QDomDocument() ;
  bool ok = doc_.setContent(s) ;
  cur_path_node_ = doc_ ;
  return ok ;
}

bool XMLTraversal::setDocument(const QDomDocument& doc) {
  doc_ = doc ;
  cur_path_node_ = doc_ ;
  return !doc_.isNull() ;
}

bool XMLTraversal::is_valid() const {
  return (!doc_.isNull()) ;
}

QDomNode XMLTraversal::cd_to_node(const QString& path) {
  if (path.isNull() && path.length()==0) {
    cur_path_node_ = doc_ ;
    return cur_path_node_ ;
  }

  if (path[0]=='/')
    cur_path_node_ = doc_ ;

  QDomNode node = cur_path_node_ ;
  QStringList toks = QStringList::split(QRegExp("\\/+"), path) ;
  for (unsigned int i=0; i<toks.size(); i++) {
    if (toks[i]=="..") {
      node = node.parentNode() ;
      if (node.isNull())
	return QDomNode() ;
      continue ;
    }
    if (toks[i]=="...") {
      node = node.parentNode() ;
      if (node.isNull())
	return QDomNode() ;
      node = node.parentNode() ;
      if (node.isNull())
	return QDomNode() ;
      continue ;
    }
    node = node.namedItem(toks[i]) ;
    if (node.isNull())
      return QDomNode() ;
  }

  return node ;
}

bool XMLTraversal::cd(const QString& path) {
  QDomNode node = cd_to_node(path) ;
  if (node.isNull())
    return false ;
  cur_path_node_ = node ;
  return true ;
}

QString XMLTraversal::pwd() const {
  if (cur_path_node_==doc_)
    return "/" ;

  QString path ;
  QDomNode node = cur_path_node_ ;
  while(!node.isDocument()) {
    path = node.nodeName()+"/"+path ;
    node = node.parentNode() ;
  }
  return path ;
}

QDomElement XMLTraversal::mkdir(const QString& d) {
  if (d.isNull() && d.isEmpty())
    return QDomElement() ;

  if (cur_path_node_.isNull())
    return QDomElement() ;

  QString path ;
  QStringList toks = QStringList::split(QRegExp("\\/+"), d) ;
  for (unsigned int i=0; i<toks.size()-1; i++) {
    if (i==0 && d[0]!='/')
      path += toks[i] ;
    else
      path += "/"+toks[i] ;
  }

  QDomNode node = cd_to_node(path) ;
  QDomElement e = doc_.createElement(toks.last()) ;
  node.appendChild(e) ;
  return e ;
}

bool XMLTraversal::rmdir(const QString& d) {
  QDomNode cur = cur_path_node_ ;
  QDomNode node = cd_to_node(d) ;
  cur_path_node_ = cur ;

  if (node.isNull())
    return false ;

  QDomNode parent = node.parentNode() ;
  if (parent.isNull())
    return false ;

  node = parent.removeChild(node) ;
  if (node.isNull())
    return false ;

  return true ;
}

/*
  bool XMLTraversal::rename(const QString& path, const QString& newname) {
  QDomNode cur = cur_path_node_ ;
  QDomNode node = cd_to_node(path) ;
  cur_path_node_ = cur ;

  if (node.isNull())
  return false ;

  if (!node.isElement())
  return false ;

  node.toElement().setTagName(newname) ;
  return true ;
  }
*/

// Possible configurations:
// ========================
//  mv /toto/titi/trululu tralala  (rename)
//  mv /toto/titi/trululu /toto/titi/tralala  (rename because same parent)
//  mv /toto/titi/trululu /tsointsoin  (move because parent differents)
bool XMLTraversal::mv(const QString& oldpath, const QString& newpath) {
  QDomNode cur = cur_path_node_ ;

  if (newpath.isNull() || newpath.isEmpty())
    return false ;

  QDomNode oldnode = cd_to_node(oldpath) ;
  cur_path_node_ = cur ;
  if (oldnode.isNull())
    return false ;

  QDomNode newnode = cd_to_node(newpath) ;
  cur_path_node_ = cur ;
  // Maybe a move command
  if (!newnode.isNull() && oldnode!=newnode) {
    if (!oldnode.parentNode().isNull()) {
      oldnode = oldnode.parentNode().removeChild(oldnode) ;
      newnode.appendChild(oldnode) ;
      return true ;
    }
    return false ;
  }

  // Or a rename command
  if (!oldnode.isElement()) // because rename the tag
    return false ;

  if (newnode.isNull()) {
    QString path ;
    QStringList toks = QStringList::split(QRegExp("\\/+"), newpath) ;
    if (toks.size()>1) {
      // assert that the parent is valid
      for (unsigned int i=0; i<toks.size()-1; i++) {
	if (i==0 && newpath[0]!='/')
	  path += toks[i] ;
	else
	  path += "/" + toks[i] ;
      }
      QDomNode parent = cd_to_node(path) ;
      cur_path_node_ = cur ;
      if (parent.isNull())
	return false ; // no valid parent

      oldnode.toElement().setTagName(toks.last()) ;
      return true ;
    } 
    else {
      oldnode.toElement().setTagName(toks.first()) ;
      return true ;
    }
  }

  return false ;
}

bool XMLTraversal::cp(const QString& source, const QString& target) {
  QDomNode cur = cur_path_node_ ;

  if (source.isNull() || source.isEmpty())
    return false ;
  if (target.isNull() || target.isEmpty())
    return false ;

  QDomNode sourcenode = cd_to_node(source) ;
  cur_path_node_ = cur ;
  if (sourcenode.isNull())
    return false ;

  QDomNode targetnode = cd_to_node(target) ;
  cur_path_node_ = cur ;
  if (targetnode.isNull())
    return false ;
	
  // Check that the target node is not a child of source
  QDomNode node = targetnode ;
  while(!node.isNull()) {
    if (node==sourcenode)
      return false ;
    node = node.parentNode() ;
  }

  // Ok, copy and move it
  targetnode.appendChild(sourcenode.cloneNode()) ;
  return true ;
  ;
}

bool XMLTraversal::exists(const QString& d) const {
  XMLTraversal* This = const_cast<XMLTraversal*>(this) ;
  QDomNode cur = cur_path_node_ ;
  QDomNode node = This->cd_to_node(d) ;
  This->cur_path_node_ = cur ;
  return !node.isNull() ;
}

QString XMLTraversal::dump() const {
  return doc_.toString() ;
}

QString XMLTraversal::currentValue() {
   QString tmp;
   QDomElement e;
   tmp = currentNode().toElement().attribute("value");
   return tmp;
}

bool XMLTraversal::setValue(QString value) {
   currentNode().toElement().setAttribute( "value", value );
   return true;
}

bool XMLTraversal::setValue(QString path, QString value) {
   QString oldpath;
   oldpath = pwd();
   cd(path);
   currentNode().toElement().setAttribute( "value", value );
   cd(oldpath);
   return true;
}
