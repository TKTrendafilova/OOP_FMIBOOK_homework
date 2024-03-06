#ifndef __URL_PUBLICATION_HPP
#define __URL_PUBLICATION_HPP
#include"Publication.hpp"

class URL :public Publication {
	char* m_description;

public:
	URL();
	URL(char*, char*);
	URL(const URL&) = delete;
	URL& operator=(const URL&) = delete;
	~URL();

	virtual void createHTML(char*) override;

	char* getDescription()const;
};

#endif