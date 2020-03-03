# SerialCord, serialize serial port from qemu into discord I/O
from disconf import *
import pexpect
import discord
import sys
from discord.ext import commands
desc = "SerialCord MikserCompany 2020"
bot = commands.Bot(command_prefix="/", description=desc)
kenOS = pexpect.spawn('qemu-system-i386 -serial stdio ../../kenos.iso')
kenOS.logfile_read = sys.stdout.buffer

@bot.command()
async def kenify(ctx, arg, *args):
    print(ctx.message.content[8:])
    kenOS.send(ctx.message.content[8:])
    kenOS.expect('kenOS: ')
    response = kenOS.before
    await ctx.send(response)

bot.run(token)