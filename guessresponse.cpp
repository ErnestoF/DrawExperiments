#include "guessresponse.h"

GuessResponse::GuessResponse(bool makeFinalGuess)
    : m_isFinalGuess(makeFinalGuess)
{
}

GuessResponse GuessResponse::makeFinalGuess(const Human &finalGuess)
{
    GuessResponse result(true);
    result.setFinalGuess(finalGuess);
    return result;
}

GuessResponse GuessResponse::makeRegularGuess(const std::set<Human> &regularGuess)
{
    GuessResponse result(false);
    result.setRegularGuess(regularGuess);
    return result;
}

bool GuessResponse::isFinalGuess() const
{
    return m_isFinalGuess;
}

std::set<Human> GuessResponse::getRegularGuess() const
{
    Q_ASSERT_X(!m_isFinalGuess, "getRegularGuess", "Getting an regular guess of a final guess is disallowed");
    Q_ASSERT_X(!m_guessedHumans.empty(), "getFinalGuess", "The guess was not set");

    return m_guessedHumans;
}

Human GuessResponse::getFinalGuess() const
{
    Q_ASSERT_X(m_isFinalGuess, "getFinalGuess", "Getting a final guess of a regular guess is disallowed");
    Q_ASSERT_X(!m_guessedHumans.empty(), "getFinalGuess", "The guess was not set");

    return *(m_guessedHumans.begin());
}

void GuessResponse::setFinalGuess(const Human &finalGuess)
{
    Q_ASSERT_X(m_isFinalGuess, "setFinalGuess", "Setting of a final guess in the regular guess is disallowed");
    m_guessedHumans.insert(finalGuess);
}

void GuessResponse::setRegularGuess(const std::set<Human> &regularGuess)
{
    Q_ASSERT_X(!m_isFinalGuess, "setRegularGuess", "Setting of an regular guess in the final guess is disallowed");
    m_guessedHumans = regularGuess;
}
