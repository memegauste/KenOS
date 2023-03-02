# SerialCord, serialize serial port from qemu into discord I/O
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


desc = 'SerialCord 2023'
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
kenOS = pexpect.spawn('qemu-system-i386 -serial stdio -drive file=../../kenos.iso,index=0,media=disk,format=raw')
kenOS.logfile_read = sys.stdout.buffer


@client.event
async def on_ready():
    """Print that bot logged in as."""
    await tree.sync()


@tree.command(description='Kenify input to SerialCord')
async def kenify(interaction, msg: str):
    kenOS.sendline(msg[:8])
    kenOS.expect(r'KenOutput: {(.*?)}')
    response = kenOS.match
    await interaction.response.send_message(
        response.group(1).decode('utf-8'),
    )

client.run(config['token'])
