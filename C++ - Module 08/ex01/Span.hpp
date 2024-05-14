#ifndef SPAN_HPP
#define SPAN_HPP
class Span{
    public:
        Span &operator=(const Span &ncopy);
        Span(const Span &ncopy);
        Span(int nbr);
        ~Span();
        Span();
};
#endif