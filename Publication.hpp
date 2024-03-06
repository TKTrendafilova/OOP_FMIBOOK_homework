#ifndef __PUBLICATION_HPP
#define __PUBLICATION_HPP

class Publication {
protected:
	char* m_content;
	unsigned m_ID;
	static unsigned m_counterID;

public:
	Publication();
	Publication(char*);
	Publication(const Publication&);
	Publication& operator=(const Publication&);
	virtual~Publication();

	void setContent(char*);
	char* getContent()const;
	unsigned getID()const;

	//Предефиниране на опретор=
	bool operator==(const Publication&);

	virtual void createHTML(char* );
};

#endif
