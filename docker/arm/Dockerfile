# syntax=docker/dockerfile:1

FROM python:3.13.5-alpine3.22
WORKDIR /code
ARG DEBIAN_FRONTEND=noninteractive
ADD . /code
COPY docker/arm/docker-scripts.sh /code/docker-scripts.sh
RUN chmod +x /code/docker-scripts.sh && /code/docker-scripts.sh

ENV PYTHONDONTWRITEBYTECODE 1
ENV PYTHONUNBUFFERED=1
ENV VIRTUAL_ENV=/opt/venv
RUN python3.13 -m venv $VIRTUAL_ENV
ENV PATH="$VIRTUAL_ENV/bin:$PATH"

RUN python3.13 -m pip install --upgrade pip && python3.13 -m pip install -r misc/SerialCord/requirements.txt
