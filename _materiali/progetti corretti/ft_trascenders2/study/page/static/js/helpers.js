import { ENDPOINTS } from "/static/js/config.js"

export const getCookie = function(name) {
	let cookieValue = null;
	if (document.cookie && document.cookie !== '') {
		const cookies = document.cookie.split(';');
		for (let i = 0; i < cookies.length; i++) {
			const cookie = cookies[i].trim();
			if (cookie.substring(0, name.length + 1) === (name + '=')) {
				cookieValue = decodeURIComponent(cookie.substring(name.length + 1));
				break;
			}
		}
	}
	return cookieValue;
}

export const getFullUrl = (category, endpoint, params = {}) => {
	let url = `${ENDPOINTS.apiBaseUrl}${ENDPOINTS[category].baseUrl}${ENDPOINTS[category].endpoints[endpoint]}`;
	for (const [key, value] of Object.entries(params))
		url = url.replace(`:${key}`, encodeURIComponent(value));
	return url;
}
