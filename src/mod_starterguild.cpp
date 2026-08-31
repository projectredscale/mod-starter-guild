#include "mod_starterguild.h"
#include "GuildMgr.h"
#include "Log.h"
#include <fmt/format.h>

void StarterGuild::OnPlayerLogin(Player* player)
{
    if (sConfigMgr->GetOption<bool>("StarterGuild.Enable", true))
    {
        if (sConfigMgr->GetOption<bool>("StarterGuild.Announce", true))
            ChatHandler(player->GetSession()).SendSysMessage("This server is running the |cff4CFF00StarterGuild |rmodule.");

        // Keep staff in the guild on every login in case they were removed while offline.
        if (player->GetSession()->IsGMAccount() && !player->GetGuild())
            AddPlayerToGuild(player);
    }
}

void StarterGuild::OnPlayerFirstLogin(Player* player)
{
    if (sConfigMgr->GetOption<bool>("StarterGuild.Enable", true) && player->GetSession()->IsGMAccount())
        AddPlayerToGuild(player);
}

void StarterGuild::AddPlayerToGuild(Player* player)
{
    auto const GUILD_NAME = sConfigMgr->GetOption<std::string>("StarterGuild.GuildName", "Redscale Staff");
    auto const GUILD_WELCOME_TEXT = sConfigMgr->GetOption<std::string>("StarterGuild.WelcomeText", "Welcome to {GUILD}, {PLAYER}.");

    Guild* guild = sGuildMgr->GetGuildByName(GUILD_NAME);

    // If the guild is present, assign the character to the guild; otherwise skip assignment.
    if (!guild)
    {
        ChatHandler(player->GetSession()).SendSysMessage(
            fmt::format("Staff guild '{}' does not exist. Create it with .guild create {}", GUILD_NAME, GUILD_NAME));
        return;
    }

    if (guild->GetMemberCount() > guildMemberCount)
    {
        ChatHandler(player->GetSession()).SendSysMessage("The staff guild has exceeded its membership limit.");
        return;
    }

    if (!guild->AddMember(player->GetGUID()))
    {
        LOG_ERROR("starterguild",
            "Failed to add player {} (GUID {}) to guild {} (ID {}).",
            player->GetPlayerName(),
            player->GetGUID().ToString(),
            guild->GetName(),
            guild->GetId());
        ChatHandler(player->GetSession()).SendSysMessage("Failed to join guild.");
        return;
    }

    // Inform the player they have joined the guild
    std::string welcome_text = fmt::format(fmt::runtime(GUILD_WELCOME_TEXT),
        fmt::arg("GUILD", guild->GetName()),
        fmt::arg("PLAYER", player->GetPlayerName()));

    if (!welcome_text.empty())
        ChatHandler(player->GetSession()).SendSysMessage(welcome_text);
}
