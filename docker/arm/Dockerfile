# syntax=docker/dockerfile:1

FROM ubuntu:noble
WORKDIR /code
ARG DEBIAN_FRONTEND=noninteractive
ADD . /code
COPY docker/arm/docker-scripts.sh /code/docker-scripts.sh
RUN chmod +x /code/docker-scripts.sh && /code/docker-scripts.sh

ENV PYTHONDONTWRITEBYTECODE 1
ENV PYTHONUNBUFFERED=1
ENV VIRTUAL_ENV=/opt/venv
RUN python3.12 -m venv $VIRTUAL_ENV
ENV PATH="$VIRTUAL_ENV/bin:$PATH"

RUN python3.12 -m pip install --upgrade pip && python3.12 -m pip install -r misc/SerialCord/requirements.txt
