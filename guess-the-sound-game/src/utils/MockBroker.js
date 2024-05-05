class MockBroker {
    constructor() {
        this.subscribers = {};
    }

    subscribe(topic, callback) {
        if (!this.subscribers[topic]) {
            this.subscribers[topic] = [];
        }
        this.subscribers[topic].push(callback);
    }

    publish(topic, message) {
        if (this.subscribers[topic]) {
            this.subscribers[topic].forEach(callback => callback(topic, message));
        }
    }
}

export default MockBroker;