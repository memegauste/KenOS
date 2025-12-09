# SerialCord, serialize serial port from qemu into discord I/O
import aiohttp
import pexpect
import discord
import sys
from discord import app_commands
from discord.ext.commands import DefaultHelpCommand
from json_utils import read_json_file


class CustomHelpCommand(DefaultHelpCommand):

    def __init__(self, **options):
        super().__init__(**options)
        self.no_category = 'General'


desc = 'SerialCord 2026'
intents = discord.Intents.default()
intents.message_content = True
activity = discord.Game('KenOS Pre-Alpha')
client = discord.Client(
    intents=intents,
    command_prefix='/',
    activity=activity,
    description=desc,
    help_command=CustomHelpCommand(),
)
tree = app_commands.CommandTree(client)
config = read_json_file('config.json')
kenOS = pexpect.spawn(
    'qemu-system-i386 --display none -serial stdio -drive file=../../kenos.iso,index=0,media=disk,format=raw',
)
kenOS.logfile_read = sys.stdout.buffer


@client.event
async def on_ready():
    """Print that bot logged in as."""
    await tree.sync()


@tree.command(description='Pokaż publiczny adres IP (tylko właściciel)')
async def get_home_ip(interaction):
    if not config.get('owner_bot_id'):
        return await interaction.response.send_message(
            '❌ Błędna konfiguracja serwera, nie jesteś administratorem!',
            ephemeral=True,
        )
    if interaction.user.id != config.get('owner_bot_id'):
        return await interaction.response.send_message(
            '❌ Ta komenda jest tylko dla właściciela bota.',
            ephemeral=True,
        )

    # odroczenie odpowiedzi
    await interaction.response.defer(ephemeral=True)

    try:
        async with aiohttp.ClientSession() as session:
            async with session.get('https://api.ipify.org') as r:
                public_ip = await r.text()
    except Exception as e:
        return await interaction.followup.send(
            f'❌ Nie udało się pobrać IP: {e}',
            ephemeral=True,
        )

    await interaction.followup.send(
        '📨 IP zostało wysłane w prywatnej wiadomości.',
        ephemeral=True,
    )

    try:
        await interaction.user.send(
            f"Publiczny adres piwnicy w Gutkowie to {public_ip}"
        )
    except:
        await interaction.followup.send(
            "❌ Nie udało się wysłać wiadomości prywatnej.",
            ephemeral=True
        )

@tree.command(description='Kenify input to SerialCord')
async def kenify(interaction, msg: str):
    kenOS.sendline(msg[:8])
    kenOS.expect([pexpect.TIMEOUT, r'KenOutput: {(.*?)}', pexpect.EOF])
    response = kenOS.match
    try:
        await interaction.response.send_message(
            response.group(1).decode('utf-8'),
        )
    except BaseException as e:
        await interaction.response.send_message(
            f'Error: {e}',
        )

client.run(config['token'])
