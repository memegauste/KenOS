# SerialCord, serialize serial port from qemu into discord I/O
from disconf import *
import pexpect
import discord
from discord.ext import commands
desc = "SerialCord MikserCompany 2020"
bot = commands.Bot(command_prefix="/", description=desc)
kenOS = pexpect.spawn('qemu-system-i386 -nographic -serial stdio ../../kenos.iso')

@bot.command()
async def kenify(ctx, arg, *args):
    kenOS.sendline(ctx.message.content[8:])
    await ctx.send(kenOS.read().decode('utf-8'))

bot.run(token)