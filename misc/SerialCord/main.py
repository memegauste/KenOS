# SerialCord, serialize serial port from qemu into discord I/O
import pexpect
import discord
import sys
from discord.ext import commands
from json_utils import read_json_file

desc = 'SerialCord 2022'
intents = discord.Intents.default()
intents.message_content = True
activity = discord.Game('KenOS Pre-Alpha')
bot = commands.Bot(
    intents=intents,
    command_prefix='/',
    activity=activity,
    description=desc,
)
config = read_json_file('config.json')
kenOS = pexpect.spawn('qemu-system-i386 -serial stdio -drive file=../../kenos.iso,index=0,media=disk,format=raw')
kenOS.logfile_read = sys.stdout.buffer


@bot.command()
async def kenify(ctx, arg, *args):
    kenOS.sendline(ctx.message.content[8:])
    kenOS.expect(r'KenOutput: {(.*?)}')
    response = kenOS.match
    await ctx.send(response.group(1).decode('utf-8'))

bot.run(config['token'])
