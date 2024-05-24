#pragma once

#include <string>

typedef struct CGI
{
	std::string     name;
	std::string     path;
} CGI;

typedef struct allow_methods
{
	bool            GET;
	bool            POST;
	bool            DELETE;
} allow_methods;

typedef struct rewrite
{
	std::string     from;
	std::string     to;
	std::string     type;
} rew;

typedef struct error_page
{
	int             code;
	std::string     path;
} error_pages;
