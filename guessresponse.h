#ifndef GUESSRESPONSE_H
#define GUESSRESPONSE_H

#include "defs.h"
#include <set>
class GuessResponse
{
public:
    static GuessResponse makeFinalGuess(human_t const& finalGuess);
    static GuessResponse makeRegularGuess(std::set<human_t> const& regularGuess);

    bool isFinalGuess() const;

    std::set<human_t> getRegularGuess() const;

    human_t getFinalGuess() const;

private:
    GuessResponse(bool makeFinalGuess);
    void setFinalGuess(human_t const& finalGuess);
    void setRegularGuess(std::set<human_t> const& regularGuess);


private:
    bool m_isFinalGuess;
    std::set<human_t> m_guessedHumans;
};

#endif // GUESSRESPONSE_H
