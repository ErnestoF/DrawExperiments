#ifndef GUESSRESPONSE_H
#define GUESSRESPONSE_H

#include "defs.h"
#include <set>
class GuessResponse
{
public:
    static GuessResponse makeFinalGuess(Human const& finalGuess);
    static GuessResponse makeRegularGuess(std::set<Human> const& regularGuess);

    bool isFinalGuess() const;

    std::set<Human> getRegularGuess() const;

    Human getFinalGuess() const;

private:
    GuessResponse(bool makeFinalGuess);
    void setFinalGuess(Human const& finalGuess);
    void setRegularGuess(std::set<Human> const& regularGuess);


private:
    bool m_isFinalGuess;
    std::set<Human> m_guessedHumans;
};

#endif // GUESSRESPONSE_H
