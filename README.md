# ![logo](https://raw.githubusercontent.com/azerothcore/azerothcore.github.io/master/images/logo-github.png) AzerothCore

## Starter Guild

- Latest build status with azerothcore:

[![Build Status](https://github.com/azerothcore/mod-starter-guild/workflows/core-build/badge.svg)](https://github.com/azerothcore/mod-starter-guild)

## Description

Redscale fork: a GM-only staff guild. Staff accounts (security >= SEC_GAMEMASTER) are added to the
guild named by `StarterGuild.GuildName` (default "Redscale Staff") on login and first login.

## Usage

- Create the staff guild ingame with `.guild create` or directly into the database.
- Edit the configuration file (the guild name must match `StarterGuild.GuildName`).
- Log in with a GM account and open the guild tab.
- Keep in mind that the limit of players is 1000 per guild.

## SQL example to create the guild

- Check that the id does not exist, and in this case, the owner will be the first creating player, generally the administrator.

```sql
DELETE FROM `guild` WHERE `name` = "Redscale Staff";
INSERT INTO `guild` (`guildid`, `name`, `leaderguid`, `motd`) VALUES
(3, "Redscale Staff", 1, "Welcome to the Redscale staff guild.");
```

## Credits

* [stygiancore](  http://stygianthebest.github.io ): (Author of the module).
* [SoulSeekkor]( https://github.com/SoulSeekkor ) cleaned up deprecation warnings and fixed naming.

* AzerothCore: [repository](https://github.com/azerothcore) - [website](http://azerothcore.org/) - [discord chat community](https://discord.gg/PaqQRkd)

## License

- This code and content is released under the [GNU AGPL v3](https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3).
