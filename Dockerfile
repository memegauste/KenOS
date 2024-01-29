# syntax=docker/dockerfile:1

FROM hoshiyamazaki/kenos-build:alphadocker
WORKDIR /code
ARG DEBIAN_FRONTEND=noninteractive
COPY ./docker-scripts.sh /code/docker-scripts.sh
RUN chmod +x /code/docker-scripts.sh && /code/docker-scripts.sh

ENV PYTHONDONTWRITEBYTECODE 1
ENV PYTHONUNBUFFERED=1
ENV VIRTUAL_ENV=/opt/venv
RUN python3.12 -m venv $VIRTUAL_ENV
ENV PATH="$VIRTUAL_ENV/bin:$PATH"

ADD . /code
RUN python3.12 -m pip install --upgrade pip && python3.12 -m pip install -r misc/SerialCord/requirements.txt
