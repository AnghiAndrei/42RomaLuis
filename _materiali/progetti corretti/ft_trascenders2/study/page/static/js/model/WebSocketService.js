export default class {
	constructor(url) {
		this.url = url;
	}

	connect() {
		if (this.socket) return ;
		this.socket = new WebSocket(this.url);

		this.socket.addEventListener('open', () => {
			console.log('WebSocket connection established');
		});

		this.socket.addEventListener('message', (event) => {
			this.onMessage(event.data);
		});

		this.socket.addEventListener('error', (error) => {
			console.error('WebSocket error:', error);
		});

		this.socket.addEventListener('close', () => {
			console.log('WebSocket connection closed');
		});
	}

	sendMessage(message) {
		if (this.socket.readyState === WebSocket.OPEN) {
			this.socket.send(JSON.stringify(message));
		} else {
			console.error('WebSocket is not open. Ready state:', this.socket.readyState);
		}
	}

	disconnect() {
		if (!this.socket) return ;
		this.socket.close();
		delete this.socket;
	}
}