#include "guiclient.h"

GuiClient::GuiClient(QString const& name)
    : AbstractClient(name)
{
}

std::set<human_t> GuiClient::guess(const GameState &/*gameState*/) const
{
    return std::set<human_t>();
}
