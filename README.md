# DocJen

## Docker Installation
- Download Docker from the official website: **Docker Desktop Installer.exe**.
- After installation, verify the installation in the terminal:

```bash
docker --version
docker info
```
- Ensure Docker Desktop is running without errors.

## Pull Jenkins Docker Image
- If you haven't already pulled the Jenkins image, run:

```bash
docker pull jenkins/jenkins:lts
```
- Verify the image:

```bash
docker images
```

## Create a Docker Network
- Create a network for Jenkins to communicate with other containers:

```bash
docker network create jenkins
```

## Create Jenkins Home Directory
- Create a persistent storage directory on your host machine:

```bash
mkdir jenkins_home
```

## Run Jenkins Container
- Run the Jenkins container with appropriate ports and volume mapping:

```bash
docker run -d --name jenkins \
  -p 8080:8080 -p 50000:50000 \
  -v jenkins_home:/var/jenkins_home \
  --network jenkins \
  jenkins/jenkins
```

## Access Jenkins Web Interface
- Open your browser and navigate to:

```bash
http://localhost:8080
```

## Retrieve Jenkins Initial Admin Password
- Find the initial admin password by running the following command in Docker:

```bash
docker exec jenkins cat /var/jenkins_home/secrets/initialAdminPassword
```
- Paste this password into the Jenkins UI.

## Install Recommended Plugins
- Once logged in, install the recommended plugins or choose plugins as per your need.

## Create Your First Pipeline Job
1. Go to **New Item**.
2. Select **Pipeline** and click **OK**.
3. In the **Pipeline Script** section, add:

```groovy
pipeline {
    agent any
    stages {
        stage('Build') {
            steps {
                echo 'Building...'
            }
        }
        stage('Test') {
            steps {
                echo 'Testing...'
            }
        }
        stage('Deploy') {
            steps {
                echo 'Deploying...'
            }
        }
    }
}
```

## Set Up Docker Integration for Builds
- Install the **Docker Pipeline Plugin**.
- Create a file named **Jenkinsfile** in your GitHub repository.

### Jenkinsfile for Linux:

```groovy
pipeline {
    agent {
        docker { image 'node:14-alpine' }
    }
    stages {
        stage('Build') {
            steps {
                sh 'node -v'
            }
        }
    }
}
```

### Jenkinsfile for Windows:

```groovy
pipeline {
    agent {
        docker { image 'node:14-alpine' }
    }
    stages {
        stage('Build') {
            steps {
                bat 'node -v'
            }
        }
    }
}
```

## Set Up Webhook for CI/CD
- Go to your **GitHub Repository** > **Settings** > **Webhooks**.
- Add a new webhook with the following details:

- **Payload URL:**

```bash
http://<your_ip_address>:8080/github-webhook/
```

- **Content Type:** `application/json`
- **Events:** Just the **push event** (or as needed).

### Find Your IP Address
- **Using ngrok:**

```bash
ngrok http 8080
```

- **Using Public IP:**
- Visit: [https://whatismyipaddress.com/](https://whatismyipaddress.com/)

## Manage and Restart Jenkins

- **View Logs:**

```bash
docker logs -f jenkins
```

- **Stop Jenkins:**

```bash
docker stop jenkins
```

- **Start Jenkins:**

```bash
docker start jenkins
