# SerialCord, serialize serial port from qemu into discord I/O
from disconf import *
import pexpect
import discord
import sys
from discord.ext import commands
desc = "SerialCord MikserCompany 2020"
bot = commands.Bot(command_prefix="/", description=desc)
kenOS = pexpect.spawn('qemu-system-i386 -serial stdio file=../../kenos.iso,index=0,format=raw')
kenOS.logfile_read = sys.stdout.buffer


@bot.command()
async def kenify(ctx, arg, *args):
    kenOS.sendline(ctx.message.content[8:])
    kenOS.expect(r'discorify: {(.*?)}')
    response = kenOS.before
    await ctx.send(response)

bot.run(token)