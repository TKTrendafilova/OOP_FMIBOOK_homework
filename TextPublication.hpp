#ifndef __TEXT_PUBLICATION_HPP
#define __TEXT_PUBLICATION_HPP

#include"Publication.hpp"

class Text : public Publication {
	//Няма собствени член-данни
public:
	Text();
	Text(char*);
	Text(const Text&) = delete;
	Text& operator=(const Text&) = delete;
	
	virtual void createHTML(char*) override;
};

#endif 

