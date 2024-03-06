#ifndef __PICTURE_PUBLICATION_HPP
#define  __PICTURE_PUBLICATION_HPP

#include"Publication.hpp"

class PicturePubl:public Publication {
	//Няма собствени член-данни
public:
	PicturePubl();
	PicturePubl(char*);
	PicturePubl(const PicturePubl&)=delete;
	PicturePubl& operator=(const PicturePubl&) = delete;

	virtual void createHTML(char* ) override;
};

#endif